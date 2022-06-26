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
			if (indices == nullptr)
			{
				if (RenderDataType == DataType::Triangles)
				{
					for (int i = 0; i < vertexCount; i += 3)
					{
						drawPrimitive<VertexInput, VertexOutput, VertexShader, FragmentShader, VertexUniform>(&(vertices[i]), pass, 0);
					}
				}
				else if (RenderDataType == DataType::TriangleStrip)
				{
					for (int i = 0; i < vertexCount - 2; i++)
					{
						drawPrimitive<VertexInput, VertexOutput, VertexShader, FragmentShader, VertexUniform>(&(vertices[i]), pass, 0);
					}
				}
			}
			else
			{
				if (RenderDataType == DataType::Triangles)
				{
					for (int i = 0; i < indexCount; i += 3)
					{
						VertexInput v[3] = {
							vertices[indices[i + 0]],
							vertices[indices[i + 1]],
							vertices[indices[i + 2]]
						};

						drawPrimitive<VertexInput, VertexOutput, VertexShader, FragmentShader, VertexUniform>(&(v[0]), pass, 0);
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

						drawPrimitive<VertexInput, VertexOutput, VertexShader, FragmentShader, VertexUniform>(&(v[0]), pass, 0);
					}
				}
			}
		}
	}

	template <typename VertexInput, typename VertexOutput, typename VertexShader, typename FragmentShader, typename VertexUniform>
	void Rasterizer::drawPrimitive(VertexInput* vertices, const Pass PASS_DATA_TYPE& pass, int index)
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

			// TODO: Clip in NDC
			// TODO: Need optimization
			if (w == 0.0f) return;
			if (pos.x < -w || pos.x > w) return;
			if (pos.y < -w || pos.y > w) return;
			if (pos.z < -w || pos.z > w) return;

			// TODO: Screen mapping and AABB
			vm[i].pos = pos / w;
			vm[i].depth = -vm[i].pos.z * 0.5f + 0.5f;

			vm[i].scrPos.x = (vm[i].pos.x * 0.5f + 0.5f) * m_bufferWidth;
			vm[i].scrPos.y = (vm[i].pos.y * -0.5f + 0.5f) * m_bufferHeight;

			vm[i].scrPixel = (IVec2)(vm[i].scrPos);

			if (i == 0)
			{
				minX = maxX = Math::Clamp(vm[i].scrPixel.x, 0, m_bufferWidth - 1);
				minY = maxY = Math::Clamp(vm[i].scrPixel.y, 0, m_bufferHeight - 1);
			}
			else
			{
				minX = Math::Clamp(Math::Min(minX, vm[i].scrPixel.x), 0, m_bufferWidth - 1);
				maxX = Math::Clamp(Math::Max(maxX, vm[i].scrPixel.x), 0, m_bufferWidth - 1);
				minY = Math::Clamp(Math::Min(minY, vm[i].scrPixel.y), 0, m_bufferHeight - 1);
				maxY = Math::Clamp(Math::Max(maxY, vm[i].scrPixel.y), 0, m_bufferHeight - 1);
			}
		}

		// TODO: FaceCull
		Vec4 v01 = vm[1].pos - vm[0].pos;
		Vec4 v02 = vm[2].pos - vm[0].pos;
		Vec3 normal = Math::Cross(v01, v02);

		if (normal.z > 0.0f)
		{
			std::swap(vm[1], vm[2]);
			std::swap(out[1], out[2]);
		}
		else if (normal.z == 0.0f)
			return;

		if (Math::Norm2(normal) <= 0)
			return;

		// TODO: interpolation
		for (int y = minY; y <= maxY; ++y)
		{
			for (int x = minX; x <= maxX; ++x)
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

				if (depth < m_depthbuffer.GetVal(x, y))
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

				// TODO: set pixel
				m_framebuffer.SetPixel(x, y, color);
			}
		}
	}
} // namespace MiniRenderer