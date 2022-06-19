#pragma once

#include "Base.h"

namespace MiniRenderer
{
	struct Quat
	{
		union
		{
			struct { float w, i, j, k; };
			struct { float r, x, y, z; };
			float e[4];
		};

		inline constexpr Quat();
		inline constexpr Quat(const Quat& src);
		inline constexpr Quat(float _w, float _i, float _j, float _k);

		inline float norm() const;
		inline Quat conj() const;
		inline Quat inverse() const;

		inline constexpr Quat& operator*=(float rhs);
		inline constexpr Quat& operator/=(float rhs);

		inline constexpr Quat& operator=(const Quat& rhs);
		inline constexpr Quat& operator+=(const Quat& rhs);
		inline constexpr Quat& operator-=(const Quat& rhs);
		inline constexpr Quat& operator*=(const Quat& rhs);
		inline Quat& operator/=(const Quat& rhs);
	};

	inline constexpr Quat operator+(const Quat& rhs);
	inline constexpr Quat operator-(const Quat& rhs);
	inline constexpr Quat operator*(const Quat& lhs, float rhs);
	inline constexpr Quat operator/(const Quat& lhs, float rhs);
	inline constexpr Quat operator*(float lhs, const Quat& rhs);
	inline constexpr Quat operator+(const Quat& lhs, const Quat& rhs);
	inline constexpr Quat operator-(const Quat& lhs, const Quat& rhs);
	inline constexpr Quat operator*(const Quat& lhs, const Quat& rhs);
	inline Quat operator/(const Quat& lhs, const Quat& rhs);

	inline constexpr bool operator==(const Quat& lhs, const Quat& rhs);
	inline constexpr bool operator!=(const Quat& lhs, const Quat& rhs);

	inline std::ostream& operator<<(std::ostream& os, const Quat& rhs);
} // namespace MiniRenderer

// inline file
#include "Quat.inl"