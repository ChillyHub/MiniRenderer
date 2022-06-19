#pragma once

#include <cstdlib>

#include "math/Math.h"

namespace MiniRenderer
{
	enum BlendMode : unsigned int
	{
		ONE_MINUS_ALPHA
	};
	
	class Framebuffer
	{
	public:
		Framebuffer() = default;
		Framebuffer(int width, int height);

		~Framebuffer();

		Vec4* GetData() const;
		Vec4 GetPixel(int x, int y) const;
		void SetPixel(int x, int y, Vec4 color);
		void MixPixel(int x, int y, Vec4 color, BlendMode blendMode);
		void SetSize(int width, int height);
		void SetBuffer();
		void Flush();
		void Clear();
	private:
		Vec4* m_data;

		int m_width;
		int m_height;
	};

	class Depthbuffer
	{
	public:
		Depthbuffer() = default;
		Depthbuffer(int width, int height);

		~Depthbuffer();

		float* GetData() const;
		float GetVal(int x, int y) const;
		void SetVal(int x, int y, float val);
		void SetSize(int width, int height);
		void SetBuffer();
		void Flush();
		void Clear();
	private:
		float* m_data;

		int m_width;
		int m_height;
	};
}