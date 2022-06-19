#include "Rasterizer.h"

#include "MiniRenderer.h"

namespace MiniRenderer
{
	Screen* Renderer::GetPtrScreen()
	{
		return &m_screen;
	}
	
	Rasterizer::Rasterizer(int width, int height, Renderer* renderer)
		: m_framebuffer(Framebuffer(width, height))
		, m_depthbuffer(Depthbuffer(width, height))
		, m_framebuffer1(Framebuffer())
		, m_framebuffer2(Framebuffer())
		, m_renderer(renderer)
	{
		m_bufferWidth = width;
		m_bufferHeight = height;
	}

	void Rasterizer::SetBufferSize(int width, int height)
	{
		m_framebuffer.SetSize(width, height);
		m_depthbuffer.SetSize(width, height);
		m_bufferWidth = width;
		m_bufferHeight = height;
	}

	Framebuffer* Rasterizer::GetFramebuffer()
	{
		return &m_framebuffer;
	}
}