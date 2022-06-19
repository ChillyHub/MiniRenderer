#pragma once

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

	class Texture2D : public Texture
	{

	};

	class TextureCube : public Texture
	{

	};
}