#include "Buffer.h"

#include <iostream>

namespace MiniRenderer
{
	Framebuffer::Framebuffer(int width, int height)
	{
		m_width = width;
		m_height = height;
		m_data = (Vec4*)malloc(width * height * sizeof(Vec4));
		std::fill(m_data, m_data + width * height, Vec4());
	}

	Framebuffer::~Framebuffer()
	{
		Clear();
	}

	Vec4* Framebuffer::GetData() const
	{
		return m_data;
	}

	Vec4 Framebuffer::GetPixel(int x, int y) const
	{
		return m_data[y * m_width + x];
	}

	void Framebuffer::SetPixel(int x, int y, Vec4 color)
	{
		assert(x < m_width&& y < m_height);
		m_data[y * m_width + x] = color;
	}

	void Framebuffer::MixPixel(int x, int y, Vec4 color, BlendMode blendMode)
	{
		assert(x < m_width&& y < m_height);
		if (blendMode == ONE_MINUS_ALPHA)
		{
			Vec4 dst = m_data[y * m_width + x];
			dst = dst * (1.0f - color.a) + Vec4(color.rgb() * color.a);
			dst.a = 1.0f;
			m_data[y * m_width + x] = dst;
		}
	}

	void Framebuffer::SetSize(int width, int height)
	{
		Clear();
		m_width = width;
		m_height = height;
		m_data = (Vec4*)malloc(width * height * sizeof(Vec4));
		std::fill(m_data, m_data + width * height, Vec4());
	}

	void Framebuffer::SetBuffer()
	{

	}

	void Framebuffer::Flush()
	{
		std::fill(m_data, m_data + m_width * m_height, Vec4());
	}

	void Framebuffer::Clear()
	{
		free(m_data);
	}

	Depthbuffer::Depthbuffer(int width, int height)
	{
		m_width = width;
		m_height = height;
		m_data = (float*)malloc(width * height * sizeof(float));
		std::fill(m_data, m_data + width * height, 0.0f);
	}

	Depthbuffer::~Depthbuffer()
	{
		Clear();
	}

	float* Depthbuffer::GetData() const
	{
		return m_data;
	}

	float Depthbuffer::GetVal(int x, int y) const
	{
		return m_data[y * m_width + x];
	}

	void Depthbuffer::SetVal(int x, int y, float val)
	{
		assert(x < m_width && y < m_height);
		m_data[y * m_width + x] = val;
	}

	void Depthbuffer::SetSize(int width, int height)
	{
		Clear();
		m_width = width;
		m_height = height;
		m_data = (float*)malloc(width * height * sizeof(float));
		std::fill(m_data, m_data + width * height, 0.0f);
	}

	void Depthbuffer::SetBuffer()
	{

	}

	void Depthbuffer::Flush()
	{
		std::fill(m_data, m_data + m_width * m_height, 0.0f);
	}

	void Depthbuffer::Clear()
	{
		free(m_data);
	}

} // namespace MiniRenderer