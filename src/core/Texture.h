#pragma once

#include "math/Math.h"

namespace MiniRenderer
{
	enum WrapMode : unsigned int
	{
		REPEAT,
		MIRROR,
		CLAMP,
		BORDER
	};

	enum FilterMode : unsigned int
	{
		NEAREST,
		BILINEAR,
		CUBIC
	};
	
	class Texture
	{
	public:
		FilterMode FilterMin;
		FilterMode FilterMax;
		WrapMode WrapType;
		bool GenerateMipmap;
	private:
		void* data;
	};

	class Sampler2D
	{
	public:
		virtual Vec4 tex2D(Vec2 uv) = 0;
	};

	class SamplerCUBE
	{
	public:
		virtual Vec4 texCUBE(Vec3 vec) = 0;
	};

	class Texture2D : public Texture, Sampler2D
	{

	};

	class TextureCube : public Texture, SamplerCUBE
	{

	};
} // namespace MiniRenderer