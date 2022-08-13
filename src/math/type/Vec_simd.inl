#pragma once

#include "Vec.h"

#include <xmmintrin.h>

namespace MiniRenderer
{
#ifdef MATH_SIMD

	template <>
	struct Vec<4, float> {
		union
		{
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			float e[4];
			__m128 ds;
		};

		Vec();
		explicit Vec(float n);
		Vec(float _x, float _y, float _z, float _w);
		explicit Vec(const float* p);
		Vec(const Vec<4, float>& src);

		template <typename A, typename B, typename C, typename D>
		Vec(A _x, B _y, C _z, D _w);
		template <typename U>
		explicit Vec(const Vec<2, U>& src);
		template <typename U>
		explicit Vec(const Vec<3, U>& src);
		template <typename U>
		explicit Vec(const Vec<3, U>& src, U _w);
		template <typename U>
		Vec(const Vec<4, U>& src);

		template <typename U>
		explicit Vec(const Vec<Type::Dynamic, U>& v);

		float& operator[] (size_t i);
		const float& operator[] (size_t i) const;

		constexpr float* data();
		constexpr size_t length() const;

		Vec<2, float> xy() const;
		Vec<2, float> rg() const;
		Vec<2, float> xz() const;
		Vec<2, float> rb() const;
		Vec<2, float> yz() const;
		Vec<2, float> gb() const;

		Vec<3, float> xyz() const;
		Vec<3, float> rgb() const;
		Vec<3, float> xyw() const;
		Vec<3, float> rga() const;
		Vec<4, float> xyzw() const;
		Vec<4, float> rgba() const;

		Vec<4, float>& operator++();
		Vec<4, float>& operator--();
		Vec<4, float> operator++(int);
		Vec<4, float> operator--(int);

		Vec<4, float>& operator= (const Vec<4, float>& rhs);
		Vec<4, float>& operator+= (const Vec<4, float>& rhs);
		Vec<4, float>& operator-= (const Vec<4, float>& rhs);
		Vec<4, float>& operator*= (const Vec<4, float>& rhs);
		Vec<4, float>& operator/= (const Vec<4, float>& rhs);

		template <typename U>
		Vec<4, float>& operator+= (U rhs);
		template <typename U>
		Vec<4, float>& operator+= (const Vec<1, U>& rhs);
		template <typename U>
		Vec<4, float>& operator-= (U rhs);
		template <typename U>
		Vec<4, float>& operator-= (const Vec<1, U>& rhs);
		template <typename U>
		Vec<4, float>& operator*= (U rhs);
		template <typename U>
		Vec<4, float>& operator*= (const Vec<1, U>& rhs);
		template <typename U>
		Vec<4, float>& operator/= (U rhs);
		template <typename U>
		Vec<4, float>& operator/= (const Vec<1, U>& rhs);

		template <typename U>
		Vec<4, float>& operator= (const Vec<4, U>& rhs);
		template <typename U>
		Vec<4, float>& operator+= (const Vec<4, U>& rhs);
		template <typename U>
		Vec<4, float>& operator-= (const Vec<4, U>& rhs);
		template <typename U>
		Vec<4, float>& operator*= (const Vec<4, U>& rhs);
		template <typename U>
		Vec<4, float>& operator/= (const Vec<4, U>& rhs);
	};

	inline Vec<4, float>::Vec()
		: ds(_mm_setzero_ps()) {}

	inline Vec<4, float>::Vec(float n) : ds(_mm_set1_ps(n)) {}

	inline Vec<4, float>::Vec(float _x, float _y, float _z, float _w)
		: ds(_mm_set_ps(_w, _z, _y, _x)) {}

	inline Vec<4, float>::Vec(const float* p)
		: ds(_mm_set_ps(p[3], p[2], p[1], p[0])) {}

	inline Vec<4, float>::Vec(const Vec<4, float>& src)
		: ds(src.ds) {}

	template <typename A, typename B, typename C, typename D>
	inline Vec<4, float>::Vec(A _x, B _y, C _z, D _w)
		: ds(_mm_set_ps(static_cast<float>(_w), static_cast<float>(_z),
			static_cast<float>(_y), static_cast<float>(_x))) {}

	template <typename U>
	inline Vec<4, float>::Vec(const Vec<2, U>& src)
		: ds(_mm_set_ps(0.0f, 0.0f,
			static_cast<float>(src.y), static_cast<float>(src.x))) {}

	template <typename U>
	inline Vec<4, float>::Vec(const Vec<3, U>& src)
		: ds(_mm_set_ps(0.0f, static_cast<float>(src.z),
			static_cast<float>(src.y), static_cast<float>(src.x))) {}

	template <typename U>
	inline Vec<4, float>::Vec(const Vec<3, U>& src, U _w)
		: ds(_mm_set_ps(static_cast<float>(_w), static_cast<float>(src.z),
			static_cast<float>(src.y), static_cast<float>(src.x))) {}

	template <typename U>
	inline Vec<4, float>::Vec(const Vec<4, U>& src)
		: ds(_mm_set_ps(static_cast<float>(src.w), static_cast<float>(src.z),
			static_cast<float>(src.y), static_cast<float>(src.x))) {}

	template <typename U>
	inline Vec<4, float>::Vec(const Vec<Type::Dynamic, U>& v)
	{
		float x = v.length() > 0 ? static_cast<float>(v[0]) : 0.0f;
		float y = v.length() > 1 ? static_cast<float>(v[1]) : 0.0f;
		float z = v.length() > 2 ? static_cast<float>(v[2]) : 0.0f;
		float w = v.length() > 3 ? static_cast<float>(v[3]) : 0.0f;
		ds = _mm_set_ps(w, z, y, x);
	}

	inline float& Vec<4, float>::operator[] (size_t i)
	{
		if (i < 0 || i >= 4)
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");
		return e[i];
	}

	inline const float& Vec<4, float>::operator[] (size_t i) const
	{
		if (i < 0 || i >= 4)
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");
		return e[i];
	}

	inline constexpr float* Vec<4, float>::data()
	{
		return &e[0];
	}

	inline constexpr size_t Vec<4, float>::length() const
	{
		return 4;
	}

	inline Vec<2, float> Vec<4, float>::xy() const
	{
		return Vec<2, float>(x, y);
	}

	inline Vec<2, float> Vec<4, float>::rg() const
	{
		return Vec<2, float>(x, y);
	}

	inline Vec<2, float> Vec<4, float>::xz() const
	{
		return Vec<2, float>(x, z);
	}

	inline Vec<2, float> Vec<4, float>::rb() const
	{
		return Vec<2, float>(x, z);
	}

	inline Vec<2, float> Vec<4, float>::yz() const
	{
		return Vec<2, float>(y, z);
	}

	inline Vec<2, float> Vec<4, float>::gb() const
	{
		return Vec<2, float>(y, z);
	}

	inline Vec<3, float> Vec<4, float>::xyz() const
	{
		return Vec<3, float>(x, y, z);
	}

	inline Vec<3, float> Vec<4, float>::rgb() const
	{
		return Vec<3, float>(x, y, z);
	}

	inline Vec<3, float> Vec<4, float>::xyw() const
	{
		return Vec<3, float>(x, y, w);
	}

	inline Vec<3, float> Vec<4, float>::rga() const
	{
		return Vec<3, float>(x, y, w);
	}

	inline Vec<4, float> Vec<4, float>::xyzw() const
	{
		return *this;
	}

	inline Vec<4, float> Vec<4, float>::rgba() const
	{
		return *this;
	}

	inline Vec<4, float>& Vec<4, float>::operator++()
	{
		ds = _mm_add_ps(ds, _mm_set1_ps(1.0f));
		return *this;
	}

	inline Vec<4, float>& Vec<4, float>::operator--()
	{
		ds = _mm_sub_ps(ds, _mm_set1_ps(1.0f));
		return *this;
	}

	inline Vec<4, float> Vec<4, float>::operator++(int)
	{
		Vec<4, float> res(*this);
		++* this;
		return res;
	}

	inline Vec<4, float> Vec<4, float>::operator--(int)
	{
		Vec<4, float> res(*this);
		--* this;
		return res;
	}

	inline Vec<4, float>& Vec<4, float>::operator= (const Vec<4, float>& rhs)
	{
		ds = rhs.ds;
		return *this;
	}

	inline Vec<4, float>& Vec<4, float>::operator+= (const Vec<4, float>& rhs)
	{
		ds = _mm_add_ps(ds, rhs.ds);
		return *this;
	}

	inline Vec<4, float>& Vec<4, float>::operator-= (const Vec<4, float>& rhs)
	{
		ds = _mm_sub_ps(ds, rhs.ds);
		return *this;
	}

	inline Vec<4, float>& Vec<4, float>::operator*= (const Vec<4, float>& rhs)
	{
		ds = _mm_mul_ps(ds, rhs.ds);
		return *this;
	}

	inline Vec<4, float>& Vec<4, float>::operator/= (const Vec<4, float>& rhs)
	{
		ds = _mm_div_ps(ds, rhs.ds);
		return *this;
	}

	template <typename U>
	inline Vec<4, float>& Vec<4, float>::operator+= (U rhs)
	{
		float n = static_cast<float>(rhs);
		ds = _mm_add_ps(ds, _mm_set1_ps(n));
		return *this;
	}

	template <typename U>
	inline Vec<4, float>& Vec<4, float>::operator+= (const Vec<1, U>& rhs)
	{
		float n = static_cast<float>(rhs[0]);
		ds = _mm_add_ps(ds, _mm_set1_ps(n));
		return *this;
	}

	template <typename U>
	inline Vec<4, float>& Vec<4, float>::operator-= (U rhs)
	{
		float n = static_cast<float>(rhs);
		ds = _mm_sub_ps(ds, _mm_set1_ps(n));
		return *this;
	}

	template <typename U>
	inline Vec<4, float>& Vec<4, float>::operator-= (const Vec<1, U>& rhs)
	{
		float n = static_cast<float>(rhs[0]);
		ds = _mm_sub_ps(ds, _mm_set1_ps(n));
		return *this;
	}

	template <typename U>
	inline Vec<4, float>& Vec<4, float>::operator*= (U rhs)
	{
		float n = static_cast<float>(rhs);
		ds = _mm_mul_ps(ds, _mm_set1_ps(n));
		return *this;
	}

	template <typename U>
	inline Vec<4, float>& Vec<4, float>::operator*= (const Vec<1, U>& rhs)
	{
		float n = static_cast<float>(rhs[0]);
		ds = _mm_mul_ps(ds, _mm_set1_ps(n));
		return *this;
	}

	template <typename U>
	inline Vec<4, float>& Vec<4, float>::operator/= (U rhs)
	{
		float n = static_cast<float>(rhs);
		ds = _mm_div_ps(ds, _mm_set1_ps(n));
		return *this;
	}

	template <typename U>
	inline Vec<4, float>& Vec<4, float>::operator/= (const Vec<1, U>& rhs)
	{
		float n = static_cast<float>(rhs[0]);
		ds = _mm_div_ps(ds, _mm_set1_ps(n));
		return *this;
	}

	template <typename U>
	inline Vec<4, float>& Vec<4, float>::operator= (const Vec<4, U>& rhs)
	{
		x = static_cast<float>(rhs.x);
		y = static_cast<float>(rhs.y);
		z = static_cast<float>(rhs.z);
		w = static_cast<float>(rhs.w);
		return *this;
	}

	template <typename U>
	inline Vec<4, float>& Vec<4, float>::operator+= (const Vec<4, U>& rhs)
	{
		x += static_cast<float>(rhs.x);
		y += static_cast<float>(rhs.y);
		z += static_cast<float>(rhs.z);
		w += static_cast<float>(rhs.w);
		return *this;
	}

	template <typename U>
	inline Vec<4, float>& Vec<4, float>::operator-= (const Vec<4, U>& rhs)
	{
		x -= static_cast<float>(rhs.x);
		y -= static_cast<float>(rhs.y);
		z -= static_cast<float>(rhs.z);
		w -= static_cast<float>(rhs.w);
		return *this;
	}

	template <typename U>
	inline Vec<4, float>& Vec<4, float>::operator*= (const Vec<4, U>& rhs)
	{
		x *= static_cast<float>(rhs.x);
		y *= static_cast<float>(rhs.y);
		z *= static_cast<float>(rhs.z);
		w *= static_cast<float>(rhs.w);
		return *this;
	}

	template <typename U>
	inline Vec<4, float>& Vec<4, float>::operator/= (const Vec<4, U>& rhs)
	{
		x /= static_cast<float>(rhs.x);
		y /= static_cast<float>(rhs.y);
		z /= static_cast<float>(rhs.z);
		w /= static_cast<float>(rhs.w);
		return *this;
	}

#endif // MATH_SIMD

} // namespace MiniRenderer