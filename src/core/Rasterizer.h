#pragma once

#include "Base.h"
#include "Buffer.h"
#include "Shader.h"
#include "Vertex.h"

#include <vector>

namespace MiniRenderer
{
	class Renderer;
	
	class Rasterizer
	{
	public:
		struct VertexMapping
		{
			Vec4 pos;
			Vec2 scrPos;
			IVec2 scrPixel;
			float depth;
		};
		DataType RenderDataType = Triangles;
		DrawType RenderDrawType = FACE;
		FaceCull RenderFaceCull = CullNone;
	public:
		Rasterizer(int width, int height, Renderer* renderer);
		Framebuffer* GetFramebuffer();
		Framebuffer* GetFramebuffer1();
		Framebuffer* GetFramebuffer2();
		Depthbuffer* GetDepthbuffer();
		template SHADER_DATA_TEMPLATE
		void SetShader(const Shader SHADER_DATA_TYPE& shader);
		void SetBufferSize(int width, int height);

		template SHADER_DATA_TEMPLATE
		void DrawCall(const Shader SHADER_DATA_TYPE& shader, VertexInput* vertices, int vertexCount,
			VertexIndex* indices = nullptr, int indexCount = 0);
		
		void Render();
		void Flush();

		void Clear();
	private:
		template <typename VertexInput, typename VertexOutput, typename VertexShader>
		void generatePrimitive(VertexInput* vertices, std::vector<VertexOutput>& primitives, const VertexShader& vs);
		template <typename VertexOutput, typename FragmentShader, typename VertexUniform>
		void drawPrimitive(VertexOutput* vertOuts, const FragmentShader& fs);
		template <typename VertexInput, typename VertexOutput, typename VertexShader, typename FragmentShader, typename VertexUniform>
		void drawPrimitives(VertexInput* vertices, const Pass PASS_DATA_TYPE& pass, int index);
		template <typename VertexOutput>
		void doClip(VertexOutput* pre, std::vector<VertexOutput>& cliped);
		template <typename VertexOutput>
		void doWClip(VertexOutput* pre, std::vector<VertexOutput>& cliped);
		void doVertexShader();
	private:
		bool InsidePlane(const Vec4& plane, const Vec4& point);
	private:
		Framebuffer m_framebuffer;  // ouput to screen
		Framebuffer m_framebuffer1; // tmp framebuffer
		Framebuffer m_framebuffer2; // tmp framebuffer
		Depthbuffer m_depthbuffer;

		Renderer* m_renderer;

		int m_bufferWidth;
		int m_bufferHeight;

		Vec4 m_backgroundColor;
	private:
		const std::vector<Vec4> c_FacesNormal = {
			{  0,  0,  1, 1 },
			{  0,  0, -1, 1 },
			{  1,  0,  0, 1 },
			{ -1,  0,  0, 1 },
			{  0,  1,  0, 1 },
			{  0, -1,  0, 1 }
		};
	};
} // namespace MiniRenderer

// inline file
#include "Rasterizer.inl"