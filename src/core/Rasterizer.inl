#pragma once

#include "Rasterizer.h"

namespace MiniRenderer
{
	template SHADER_DATA_TEMPLATE
	void Rasterizer::DrawCall(const Shader SHADER_DATA_TYPE& shader, VertexInput* vertices, int vertexCount,
			VertexIndex* indices, int indexCount)
	{
		m_framebuffer.Flush();
		m_depthbuffer.Flush();
		
		for (const auto& pass : shader.m_pass)
		{
			std::vector<VertexOutput> primitives;
			
			if (indices == nullptr)
			{
				primitives.reserve(vertexCount);
				
				if (RenderDataType == DataType::Triangles)
				{
					for (int i = 0; i < vertexCount; i += 3)
					{
						generatePrimitive(&(vertices[i]), primitives, pass.vert);
						
						//drawPrimitive<VertexInput, VertexOutput, VertexShader, FragmentShader, VertexUniform>(&(vertices[i]), pass, 0);
					}
				}
				else if (RenderDataType == DataType::TriangleStrip)
				{
					for (int i = 0; i < vertexCount - 2; i++)
					{
						std::swap(vertices[i], vertices[i + 1]);
						generatePrimitive(&(vertices[i]), primitives, pass.vert);

						//drawPrimitive<VertexInput, VertexOutput, VertexShader, FragmentShader, VertexUniform>(&(vertices[i]), pass, 0);
					}
				}
			}
			else
			{
				primitives.reserve(indexCount);
				
				if (RenderDataType == DataType::Triangles)
				{
					for (int i = 0; i < indexCount; i += 3)
					{
						VertexInput v[3] = {
							vertices[indices[i + 0]],
							vertices[indices[i + 1]],
							vertices[indices[i + 2]]
						};

						generatePrimitive(&(v[0]), primitives, pass.vert);

						//drawPrimitive<VertexInput, VertexOutput, VertexShader, FragmentShader, VertexUniform>(&(v[0]), pass, 0);
					}
				}
				else if (RenderDataType == DataType::TriangleStrip)
				{
					for (int i = 0; i < indexCount - 2; i++)
					{
						VertexInput v[3] = {
							vertices[indices[i + 0]],
							vertices[indices[i + 1]],
							vertices[indices[i + 2]]
						};

						generatePrimitive(&(v[0]), primitives, pass.vert);

						//drawPrimitive<VertexInput, VertexOutput, VertexShader, FragmentShader, VertexUniform>(&(v[0]), pass, 0);
					}
				}
			}

			int end = primitives.size() - 2;
			for (int i = 0; i < end; i += 3)
			{
				drawPrimitive<VertexOutput, FragmentShader, VertexUniform>(primitives.data() + i, pass.frag);
			}
		}
	}

	template <typename VertexInput, typename VertexOutput, typename VertexShader>
	inline void Rasterizer::generatePrimitive(VertexInput* vertices, std::vector<VertexOutput>& primitives, const VertexShader& vs)
	{
		VertexOutput out[3];
		std::vector<VertexOutput> newOut;

		for (int i = 0; i < 3; ++i)
		{
			out[i] = vs(vertices[i]);
		}

		doWClip(out, newOut);

		for (int i = 1; i < (int)newOut.size() - 1; ++i)
		{
			primitives.push_back(newOut[0]);
			primitives.push_back(newOut[i]);
			primitives.push_back(newOut[i + 1]);
		}
	}

	template <typename VertexOutput, typename FragmentShader, typename VertexUniform>
	inline void Rasterizer::drawPrimitive(VertexOutput* vertOuts, const FragmentShader& fs)
	{
		VertexMapping vm[3];
		VertexOutput out[3];
		out[0] = vertOuts[0];
		out[1] = vertOuts[1];
		out[2] = vertOuts[2];

		int minX, minY, maxX, maxY;

		for (int i = 0; i < 3; ++i)
		{
			Vec4 pos = out[i].pos;
			float w = pos.w;

			// TODO: Screen mapping and AABB
			vm[i].pos = pos / w;
			vm[i].depth = -vm[i].pos.z * 0.5f + 0.5f;

			vm[i].scrPos.x = (vm[i].pos.x * 0.5f + 0.5f) * m_bufferWidth;
			vm[i].scrPos.y = (vm[i].pos.y * -0.5f + 0.5f) * m_bufferHeight;

			vm[i].scrPixel = (IVec2)(vm[i].scrPos);

			if (i == 0)
			{
				minX = Math::Clamp(vm[i].scrPixel.x, 0, m_bufferWidth);
				maxX = Math::Clamp(vm[i].scrPixel.x + 1, 0, m_bufferWidth);
				minY = Math::Clamp(vm[i].scrPixel.y, 0, m_bufferHeight);
				maxY = Math::Clamp(vm[i].scrPixel.y + 1, 0, m_bufferHeight);
			}
			else
			{
				minX = Math::Clamp(Math::Min(minX, vm[i].scrPixel.x), 0, m_bufferWidth);
				maxX = Math::Clamp(Math::Max(maxX, vm[i].scrPixel.x + 1), 0, m_bufferWidth);
				minY = Math::Clamp(Math::Min(minY, vm[i].scrPixel.y), 0, m_bufferHeight);
				maxY = Math::Clamp(Math::Max(maxY, vm[i].scrPixel.y + 1), 0, m_bufferHeight);
			}
		}

		// XY Clip
		if (minX == maxX || minY == maxY)
			return;

		// TODO: FaceCull
		Vec4 v01 = vm[1].pos - vm[0].pos;
		Vec4 v02 = vm[2].pos - vm[0].pos;
		Vec3 normal = Math::Cross(v01, v02);

		if (RenderFaceCull == FaceCull::CullBack && normal.z > 0.0f)
		{
			return;
		}
		if (RenderFaceCull == FaceCull::CullFront && normal.z < 0.0f)
		{
			return;
		}
		if (RenderFaceCull == FaceCull::CullNone && normal.z > 0.0f)
		{
			std::swap(vm[1], vm[2]);
			std::swap(out[1], out[2]);
		}
		else if (normal.z == 0.0f)
			return;

		if (Math::Norm2(normal) <= 0)
			return;

		// TODO: interpolation
		for (int y = minY; y < maxY; ++y)
		{
			for (int x = minX; x < maxX; ++x)
			{
				Vec2 vo = { x + 0.5f, y + 0.5f };

				Vec2 vo0 = vm[0].scrPos + 0.5f - vo;
				Vec2 vo1 = vm[1].scrPos + 0.5f - vo;
				Vec2 vo2 = vm[2].scrPos + 0.5f - vo;

				float sa = Math::Cross(vo1, vo2);
				float sb = Math::Cross(vo2, vo0);
				float sc = Math::Cross(vo0, vo1);
				float s = sa + sb + sc;

				if (sa < 0.0f || sb < 0.0f || sc < 0.0f || s == 0.0f)
					continue;

				float a = sa / s;
				float b = sb / s;
				float c = sc / s;

				// TODO: deepth test (Early-Z)
				float depth = a * vm[0].depth + b * vm[1].depth + c * vm[2].depth;

				if (depth < m_depthbuffer.GetVal(x, y) || depth > 1.0f)
					continue;
				m_depthbuffer.SetVal(x, y, depth);

				// TODO: vertex output interpolation
				VertexOutput vertexOut;

				int size = sizeof(VertexOutput) / sizeof(float);
				for (int i = 0; i < size; ++i)
				{
					float oa = *((float*)(&out[0]) + i);
					float ob = *((float*)(&out[1]) + i);
					float oc = *((float*)(&out[2]) + i);
					*((float*)&vertexOut + i) = a * oa + b * ob + c * oc;
				}

				// TODO: fragment shader
				Vec4 color = fs(vertexOut);

				// TODO: stencil test

				// TODO: alpha test

				// TODO: blend

				// TODO: toon mapping

				// TODO: set pixel
				m_framebuffer.SetPixel(x, y, color);
			}
		}
	}

	template <typename VertexInput, typename VertexOutput, typename VertexShader, typename FragmentShader, typename VertexUniform>
	void Rasterizer::drawPrimitives(VertexInput* vertices, const Pass PASS_DATA_TYPE& pass, int index)
	{
		VertexInput v[3] = {
			vertices[0],
			vertices[1],
			vertices[2]
		};

		VertexMapping vm[3];
		VertexOutput out[3];

		int minX, minY, maxX, maxY;

		for (int i = 0; i < 3; ++i)
		{
			// TODO: Vertex shader
			out[i] = pass.vert(v[i]);

			Vec4 pos = out[i].pos;
			float w = pos.w;

			// TODO: W Clip

			// TODO: Screen mapping and AABB
			vm[i].pos = pos / w;
			vm[i].depth = -vm[i].pos.z * 0.5f + 0.5f;

			vm[i].scrPos.x = (vm[i].pos.x * 0.5f + 0.5f) * m_bufferWidth;
			vm[i].scrPos.y = (vm[i].pos.y * -0.5f + 0.5f) * m_bufferHeight;

			vm[i].scrPixel = (IVec2)(vm[i].scrPos);

			if (i == 0)
			{
				minX = Math::Clamp(vm[i].scrPixel.x, 0, m_bufferWidth);
				maxX = Math::Clamp(vm[i].scrPixel.x + 1, 0, m_bufferWidth);
				minY = Math::Clamp(vm[i].scrPixel.y, 0, m_bufferHeight);
				maxY = Math::Clamp(vm[i].scrPixel.y + 1, 0, m_bufferHeight);
			}
			else
			{
				minX = Math::Clamp(Math::Min(minX, vm[i].scrPixel.x), 0, m_bufferWidth);
				maxX = Math::Clamp(Math::Max(maxX, vm[i].scrPixel.x + 1), 0, m_bufferWidth);
				minY = Math::Clamp(Math::Min(minY, vm[i].scrPixel.y), 0, m_bufferHeight);
				maxY = Math::Clamp(Math::Max(maxY, vm[i].scrPixel.y + 1), 0, m_bufferHeight);
			}
		}

		// XY Clip
		if (minX == maxX || minY == maxY)
			return;

		// TODO: FaceCull
		Vec4 v01 = vm[1].pos - vm[0].pos;
		Vec4 v02 = vm[2].pos - vm[0].pos;
		Vec3 normal = Math::Cross(v01, v02);

		if (RenderFaceCull == FaceCull::CullBack && normal.z > 0.0f)
		{
			return;
		}
		if (RenderFaceCull == FaceCull::CullFront && normal.z < 0.0f)
		{
			return;
		}
		if (RenderFaceCull == FaceCull::CullNone && normal.z > 0.0f)
		{
			std::swap(vm[1], vm[2]);
			std::swap(out[1], out[2]);
		}
		else if (normal.z == 0.0f)
			return;

		if (Math::Norm2(normal) <= 0)
			return;

		// TODO: interpolation
		for (int y = minY; y < maxY; ++y)
		{
			for (int x = minX; x < maxX; ++x)
			{
				Vec2 vo = { x + 0.5f, y + 0.5f };

				Vec2 vo0 = vm[0].scrPos + 0.5f - vo;
				Vec2 vo1 = vm[1].scrPos + 0.5f - vo;
				Vec2 vo2 = vm[2].scrPos + 0.5f - vo;

				float sa = Math::Cross(vo1, vo2);
				float sb = Math::Cross(vo2, vo0);
				float sc = Math::Cross(vo0, vo1);
				float s = sa + sb + sc;

				if (sa < 0.0f || sb < 0.0f || sc < 0.0f || s == 0.0f)
					continue;

				float a = sa / s;
				float b = sb / s;
				float c = sc / s;

				// TODO: deepth test (Early-Z)
				float depth = a * vm[0].depth + b * vm[1].depth + c * vm[2].depth;

				if (depth < m_depthbuffer.GetVal(x, y) || depth > 1.0f)
					continue;
				m_depthbuffer.SetVal(x, y, depth);

				// TODO: vertex output interpolation
				VertexOutput vertexOut;

				int size = sizeof(VertexOutput) / sizeof(float);
				for (int i = 0; i < size; ++i)
				{
					float oa = *((float*)(&out[0]) + i);
					float ob = *((float*)(&out[1]) + i);
					float oc = *((float*)(&out[2]) + i);
					*((float*)&vertexOut + i) = a * oa + b * ob + c * oc;
				}

				// TODO: fragment shader
				Vec4 color = pass.frag(vertexOut);

				// TODO: stencil test

				// TODO: alpha test

				// TODO: blend

				// TODO: toon mapping

				// TODO: set pixel
				m_framebuffer.SetPixel(x, y, color);
			}
		}
	}

	template <typename VertexOutput>
	inline void Rasterizer::doClip(VertexOutput* pre, std::vector<VertexOutput>& cliped)
	{
		for (int i = 0; i < 3; ++i)
		{
			Vec4 pos = pre[i].pos;
			float w = pos.w;

			if (w == 0.0f) break;
			if (pos.x > w || pos.x < -w) break;
			if (pos.y > w || pos.y < -w) break;
			if (pos.z > w || pos.z < -w) break;

			cliped.resize(3);
			cliped[0] = pre[0];
			cliped[1] = pre[1];
			cliped[2] = pre[2];
			return;
		}

		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				Vec4 a = pre[j].pos;
				Vec4 b = pre[(j + 2) % 3].pos;
			}
		}
	}

	template <typename VertexOutput>
	inline void Rasterizer::doWClip(VertexOutput* pre, std::vector<VertexOutput>& cliped)
	{
		int c = 0;
		
		for (int i = 0; i < 3; ++i)
		{
			Vec4 pos = pre[i].pos;
			float w = pos.w;

			if (w == 0.0f) break;
			if (pos.x > w || pos.x < -w) break;
			if (pos.y > w || pos.y < -w) break;
			if (pos.z > w || pos.z < -w) break;

			++c;
		}
		if (c == 3)
		{
			cliped.resize(3);
			cliped[0] = pre[0];
			cliped[1] = pre[1];
			cliped[2] = pre[2];
			return;
		}
		
		c = 0;
		for (int i = 0; i < 3; ++i)
		{
			Vec4 pos = pre[i].pos;
			float w = pos.w;

			if (pos.x < w && pos.x > -w) break;
			if (pos.y < w && pos.y > -w) break;
			if (pos.z < w && pos.z > -w) break;

			++c;
		}
		if (c == 3)
		{
			return;
		}

		cliped.reserve(3);
		for (int i = 0; i < 3; ++i)
		{
			Vec4 posa = pre[i].pos;
			Vec4 posb = pre[(i + 2) % 3].pos;
			float wa = posa.w;
			float wb = posb.w;

			if (posa.z < -wa)
			{
				if (posb.z >= -wb)
				{
					//float a = (posb.z / wb + 1.0f) / (posb.z / wb - posa.z / wa);
					float a = (posb.z + posb.w) / (posb.z + posb.w - posa.z);
					float b = 1.0f - a;
					
					VertexOutput vo;
					int size = sizeof(VertexOutput) / sizeof(float);
					for (int j = 0; j < size; ++j)
					{
						float oa = *((float*)(&pre[i]) + j);
						float ob = *((float*)(&pre[(i + 2) % 3]) + j);
						*((float*)&vo + j) = a * oa + b * ob;
					}
					cliped.push_back(vo);
				}
			}
			else
			{
				if (posb.z < -wb)
				{
					//float b = (posa.z / wa + 1.0f) / (posa.z / wa - posb.z / wb);
					float b = (posa.z + posa.w) / (posa.z + posa.w - posb.z);
					float a = 1.0f - b;

					VertexOutput vo;
					int size = sizeof(VertexOutput) / sizeof(float);
					for (int j = 0; j < size; ++j)
					{
						float oa = *((float*)(&pre[i]) + j);
						float ob = *((float*)(&pre[(i + 2) % 3]) + j);
						*((float*)&vo + j) = a * oa + b * ob;
					}
					cliped.push_back(vo);
				}
				
				cliped.push_back(pre[i]);
			}
		}
	}
} // namespace MiniRenderer