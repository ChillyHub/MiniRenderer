#pragma once

#include "math/Math.h"

namespace MiniRenderer
{
	//struct VertexInput {};
	
	struct VertexInputNative// : VertexInput
	{
		Vec3 vertex;
		Vec2 texcoord;
	};

	struct VertexInputColor// : VertexInput
	{
		Vec3 vertex;
		Vec2 texcoord;
		Vec4 color;
	};

	struct VertexInputNormal// : VertexInput
	{
		Vec3 vertex;
		Vec2 texcoord;
		Vec3 normal;
	};

	struct VertexInputTangent// : VertexInput
	{
		Vec3 vertex;
		Vec2 texcoord;
		Vec3 normal;
		Vec3 tangent;
	};

	struct VertexOut
	{
		Vec4 pos;
	};

	typedef unsigned int VertexIndex;
} // namespace MiniRenderer