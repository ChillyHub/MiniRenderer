#pragma once

#include "math/Math.h"

namespace MiniRenderer
{
	//struct VertexInput {};
	
	struct VertexInputNative// : VertexInput
	{
		Vec4 vertex;
		Vec2 texcoord;
	};

	struct VertexInputColor// : VertexInput
	{
		Vec4 vertex;
		Vec2 texcoord;
		Vec4 color;
	};

	struct VertexInputNormal// : VertexInput
	{
		Vec4 vertex;
		Vec2 texcoord;
		Vec3 normal;
	};

	struct VertexInputTangent// : VertexInput
	{
		Vec4 vertex;
		Vec2 texcoord;
		Vec3 normal;
		Vec3 tangent;
	};

	struct VertexIndex {}; 

	struct VertexOut
	{
		Vec4 pos;
	};

	//struct VertexUniform {};
}