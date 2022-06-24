#pragma once

#include "Quat.h"

namespace MiniRenderer
{
	constexpr Quat::Quat()
		: w(1.0f), i(0.0f), j(0.0f), k(0.0f) {}

	constexpr Quat::Quat(const Quat& src)
		: w(src.w), i(src.i), j(src.j), k(src.k) {}

	constexpr Quat::Quat(float _w, const Vec3& v)
		: w(_w), i(v.x), j(v.y), k(v.z) {}

	constexpr Quat::Quat(float _w, float _i, float _j, float _k)
		: w(_w), i(_i), j(_j), k(_k) {}

	float Quat::norm() const
	{
		return std::sqrt(w * w + i * i + j * j + k * k);
	}

	Quat Quat::conj() const
	{
		Quat q(*this);
		q.i = -q.i;
		q.j = -q.j;
		q.k = -q.k;
		return q;
	}

	Quat Quat::inverse() const
	{
		return conj() / norm();
	}

	constexpr Quat& Quat::operator*=(float rhs)
	{
		w *= rhs;
		i *= rhs;
		j *= rhs;
		k *= rhs;
		return *this;
	}

	constexpr Quat& Quat::operator/=(float rhs)
	{
		w /= rhs;
		i /= rhs;
		j /= rhs;
		k /= rhs;
		return *this;
	}

	constexpr Quat& Quat::operator=(const Quat& rhs)
	{
		w = rhs.w;
		i = rhs.i;
		j = rhs.j;
		k = rhs.k;
		return *this;
	}

	constexpr Quat& Quat::operator+=(const Quat& rhs)
	{
		w += rhs.w;
		i += rhs.i;
		j += rhs.j;
		k += rhs.k;
		return *this;
	}

	constexpr Quat& Quat::operator-=(const Quat& rhs)
	{
		w -= rhs.w;
		i -= rhs.i;
		j -= rhs.j;
		k -= rhs.k;
		return *this;
	}

	constexpr Quat& Quat::operator*=(const Quat& rhs)
	{
		auto _w = w * rhs.w - i * rhs.i - j * rhs.j - k * rhs.k;
		auto _i = w * rhs.i + i * rhs.w + j * rhs.k - k * rhs.j;
		auto _j = w * rhs.j + j * rhs.w + k * rhs.i - i * rhs.k;
		auto _k = w * rhs.k + k * rhs.w + i * rhs.j - j * rhs.i;
		w = _w;
		i = _i;
		j = _j;
		k = _k;
		return *this;
	}

	Quat& Quat::operator/=(const Quat& rhs)
	{
		*this *= rhs.inverse();
		return *this;
	}

	constexpr Quat operator+(const Quat& rhs)
	{
		return rhs;
	}

	constexpr Quat operator-(const Quat& rhs)
	{
		Quat q;
		q.w = -rhs.w;
		q.i = -rhs.i;
		q.j = -rhs.j;
		q.k = -rhs.k;
		return q;
	}

	constexpr Quat operator*(const Quat& lhs, float rhs)
	{
		Quat q(lhs);
		q *= rhs;
		return q;
	}

	constexpr Quat operator/(const Quat& lhs, float rhs)
	{
		Quat q(lhs);
		q /= rhs;
		return q;
	}

	constexpr Quat operator*(float lhs, const Quat& rhs)
	{
		Quat q(rhs);
		q *= lhs;
		return q;
	}

	constexpr Quat operator+(const Quat& lhs, const Quat& rhs)
	{
		Quat q(lhs);
		q += rhs;
		return q;
	}

	constexpr Quat operator-(const Quat& lhs, const Quat& rhs)
	{
		Quat q(lhs);
		q -= rhs;
		return q;
	}

	constexpr Quat operator*(const Quat& lhs, const Quat& rhs)
	{
		Quat q(lhs);
		q *= rhs;
		return q;
	}

	Quat operator/(const Quat& lhs, const Quat& rhs)
	{
		Quat q(lhs);
		q /= rhs;
		return q;
	}



	constexpr bool operator==(const Quat& lhs, const Quat& rhs)
	{
		return lhs.w == rhs.w && lhs.i == rhs.i
			&& lhs.j == rhs.j && lhs.k == rhs.k;
	}

	constexpr bool operator!=(const Quat& lhs, const Quat& rhs)
	{
		return !(lhs == rhs);
	}

	std::ostream& operator<<(std::ostream& os, const Quat& rhs)
	{
		os << "[ " << rhs.w
			<< " (" << rhs.i
			<< ", " << rhs.j
			<< ", " << rhs.k
			<< ") ]";
		return os;
	}
}