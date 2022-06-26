#include "Light.h"

namespace MiniRenderer
{
	Vec3 Light::GetObjToLightDir(const Vec3& worldPos) const
	{
		if (LightMode == DirectLight)
			return Math::Rotate(Rotation, Vec3(0.0f, 0.0f, 1.0f));
		return Math::Normailzed(Position - worldPos);
	}

	Vec3 Light::GetLightToObjDir(const Vec3& worldPos) const
	{
		if (LightMode == DirectLight)
			return Math::Rotate(Rotation, Vec3(0.0f, 0.0f, -1.0f));
		return Math::Normailzed(worldPos - Position);
	}
} // namespace MiniRenderer