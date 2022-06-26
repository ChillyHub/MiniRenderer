#pragma once

#include "math/Math.h"

namespace MiniRenderer
{
	enum LightType
	{
		DirectLight,
		PointLight,
		FaceLight,
		SpotLight
	};
	
	class Light
	{
	public:
		Vec3 Position       = { 0.0f, 0.0f, 2.0f };
		Quat Rotation       = { 1.0f, 0.0f, 0.0f, 0.0f };
		Vec4 LightColor     = { 1.0f, 1.0f, 1.0f, 1.0f };
		LightType LightMode = LightType::DirectLight;
	public:
		Light(Vec3 position) : Position(position) {}
	public:
		Vec3 GetObjToLightDir(const Vec3& worldPos) const;
		Vec3 GetLightToObjDir(const Vec3& worldPos) const;
	};
} // namespace MiniRenderer