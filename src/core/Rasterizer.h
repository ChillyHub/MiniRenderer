#pragma once

#include "Base.h"
#include "Buffer.h"
#include "Shader.h"
#include "Vertex.h"

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
		template <typename VertexInput, typename VertexOutput, typename VertexShader, typename FragmentShader, typename VertexUniform>
		void drawPrimitive(VertexInput* vertices, const Pass PASS_DATA_TYPE& pass, int index);
		void doClip();
		void doVertexShader();
	private:
		Framebuffer m_framebuffer;  // ouput to screen
		Framebuffer m_framebuffer1; // tmp framebuffer
		Framebuffer m_framebuffer2; // tmp framebuffer
		Depthbuffer m_depthbuffer;

		Renderer* m_renderer;

		int m_bufferWidth;
		int m_bufferHeight;

		Vec4 m_backgroundColor;
	};
} // namespace MiniRenderer

// inline file
#include "Rasterizer.inl"