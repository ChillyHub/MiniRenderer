#pragma once

#include "Vec.h"

namespace MiniRenderer
{
	/////////////////////////////////////////////////////
	// Vector: Vec<N, T>, Vec2, Vec3, Vec4 --------------
	//---------------------------------------------------

	// Vec ----------------------------------------------
	// --------------------------------------------------
	template <size_t N, typename T>
	inline constexpr Vec<N, T>::Vec()
	{
		for (size_t i = 0; i < N; ++i)
			e[i] = T();
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T>::Vec(T n)
	{
		for (size_t i = 0; i < N; ++i)
			e[i] = n;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T>::Vec(const T* p)
	{
		for (size_t i = 0; i < N; ++i)
			e[i] = p[i];
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T>::Vec(const Vec<N, T>& src)
	{
		for (size_t i = 0; i < N; ++i)
			e[i] = src.e[i];
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>::Vec(const std::initializer_list<U>& l)
	{
		auto it = l.begin();
		for (size_t i = 0; i < N; ++i)
			e[i] = static_cast<T>(*it++);
	}

	template <size_t N, typename T>
	template <size_t M, typename U>
	inline constexpr Vec<N, T>::Vec(const Vec<M, U>& src)
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (i < M)
				e[i] = static_cast<T>(src[i]);
			else
				e[i] = T();
		}
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>::Vec(const Vec<Type::Dynamic, U>& v)
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (i < v.length())
				e[i] = static_cast<T>(v[i]);
			else
				e[i] = T();
		}
	}

	template <size_t N, typename T>
	inline constexpr T& Vec<N, T>::operator[] (size_t i)
	{
		if (i < 0 || i >= N)
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");
		return e[i];
	}

	template <size_t N, typename T>
	inline constexpr const T& Vec<N, T>::operator[] (size_t i) const
	{
		if (i < 0 || i >= N)
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");
		return e[i];
	}

	template <size_t N, typename T>
	inline constexpr T* Vec<N, T>::data()
	{
		return &e[0];
	}

	template <size_t N, typename T>
	inline constexpr size_t Vec<N, T>::length() const
	{
		return N;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T>& Vec<N, T>::operator++()
	{
		for (size_t i = 0; i < N; ++i)
			++e[i];
		return *this;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T>& Vec<N, T>::operator--()
	{
		for (size_t i = 0; i < N; ++i)
			--e[i];
		return *this;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> Vec<N, T>::operator++(int)
	{
		Vec<N, T> res(*this);
		++* this;
		return res;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> Vec<N, T>::operator--(int)
	{
		Vec<N, T> res(*this);
		--* this;
		return res;
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>& Vec<N, T>::operator= (const Vec<N, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			e[i] = static_cast<T>(rhs.e[i]);
		}
		return *this;
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>& Vec<N, T>::operator+= (U rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			e[i] += static_cast<T>(rhs);
		}
		return *this;
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>& Vec<N, T>::operator+= (const Vec<1, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			e[i] += static_cast<T>(rhs.e[0]);
		}
		return *this;
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>& Vec<N, T>::operator+= (const Vec<N, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			e[i] += static_cast<T>(rhs.e[i]);
		}
		return *this;
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>& Vec<N, T>::operator-= (U rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			e[i] -= static_cast<T>(rhs);
		}
		return *this;
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>& Vec<N, T>::operator-= (const Vec<1, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			e[i] -= static_cast<T>(rhs.e[0]);
		}
		return *this;
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>& Vec<N, T>::operator-= (const Vec<N, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			e[i] -= static_cast<T>(rhs.e[i]);
		}
		return *this;
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>& Vec<N, T>::operator*= (U rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			e[i] *= static_cast<T>(rhs);
		}
		return *this;
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>& Vec<N, T>::operator*= (const Vec<1, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			e[i] *= static_cast<T>(rhs.e[0]);
		}
		return *this;
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>& Vec<N, T>::operator*= (const Vec<N, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			e[i] *= static_cast<T>(rhs.e[i]);
		}
		return *this;
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>& Vec<N, T>::operator/= (U rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			e[i] /= static_cast<T>(rhs);
		}
		return *this;
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>& Vec<N, T>::operator/= (const Vec<1, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			e[i] /= static_cast<T>(rhs.e[0]);
		}
		return *this;
	}

	template <size_t N, typename T>
	template <typename U>
	inline constexpr Vec<N, T>& Vec<N, T>::operator/= (const Vec<N, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			e[i] /= static_cast<T>(rhs.e[i]);
		}
		return *this;
	}

	// Vec2 ---------------------------------------------
	// --------------------------------------------------
	template <typename T>
	inline constexpr Vec<2, T>::Vec() : x(T()), y(T()) {}

	template <typename T>
	inline constexpr Vec<2, T>::Vec(T _x, T _y) : x(_x), y(_y) {}

	template <typename T>
	inline constexpr Vec<2, T>::Vec(T n) : x(n), y(n) {}

	template <typename T>
	inline constexpr Vec<2, T>::Vec(const T* p) : x(p[0]), y(p[1]) {}

	template <typename T>
	inline constexpr Vec<2, T>::Vec(const Vec<2, T>& src) : x(src.x), y(src.y) {}

	template <typename T>
	template <typename A, typename B>
	inline constexpr Vec<2, T>::Vec(A _x, B _y) 
		: x(static_cast<T>(_x)), y(static_cast<T>(_y)) {}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>::Vec(const Vec<2, U>& src)
		: x(static_cast<T>(src.x)), y(static_cast<T>(src.y)) {}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>::Vec(const Vec<3, U>& src)
		: x(static_cast<T>(src.x)), y(static_cast<T>(src.y)) {}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>::Vec(const Vec<4, U>& src)
		: x(static_cast<T>(src.x)), y(static_cast<T>(src.y)) {}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>::Vec(const Vec<Type::Dynamic, U>& v)
	{
		x = v.length() > 0 ? static_cast<T>(v[0]) : T();
		y = v.length() > 1 ? static_cast<T>(v[1]) : T();
	}

	template <typename T>
	inline constexpr T& Vec<2, T>::operator[] (size_t i)
	{
		if (i < 0 || i >= 2)
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");
		return e[i];
	}

	template <typename T>
	inline constexpr const T& Vec<2, T>::operator[] (size_t i) const
	{
		if (i < 0 || i >= 2)
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");
		return e[i];
	}

	template <typename T>
	inline constexpr T* Vec<2, T>::data()
	{
		return &e[0];
	}

	template <typename T>
	inline constexpr size_t Vec<2, T>::length() const
	{
		return 2;
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<2, T>::xy() const
	{
		return Vec<2, T>(x, y);
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<2, T>::rg() const
	{
		return Vec<2, T>(x, y);
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<2, T>::uv() const
	{
		return Vec<2, T>(x, y);
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<2, T>::st() const
	{
		return Vec<2, T>(x, y);
	}

	template <typename T>
	inline constexpr Vec<2, T>& Vec<2, T>::operator++()
	{
		++x;
		++y;
		return *this;
	}

	template <typename T>
	inline constexpr Vec<2, T>& Vec<2, T>::operator--()
	{
		--x;
		--y;
		return *this;
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<2, T>::operator++(int)
	{
		Vec<2, T> res(*this);
		++* this;
		return res;
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<2, T>::operator--(int)
	{
		Vec<2, T> res(*this);
		--* this;
		return res;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>& Vec<2, T>::operator= (const Vec<2, U>& rhs)
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>& Vec<2, T>::operator+= (U rhs)
	{
		x += static_cast<T>(rhs);
		y += static_cast<T>(rhs);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>& Vec<2, T>::operator+= (const Vec<1, U>& rhs)
	{
		x += static_cast<T>(rhs[0]);
		y += static_cast<T>(rhs[0]);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>& Vec<2, T>::operator+= (const Vec<2, U>& rhs)
	{
		x += static_cast<T>(rhs.x);
		y += static_cast<T>(rhs.y);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>& Vec<2, T>::operator-= (U rhs)
	{
		x -= static_cast<T>(rhs);
		y -= static_cast<T>(rhs);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>& Vec<2, T>::operator-= (const Vec<1, U>& rhs)
	{
		x -= static_cast<T>(rhs[0]);
		y -= static_cast<T>(rhs[0]);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>& Vec<2, T>::operator-= (const Vec<2, U>& rhs)
	{
		x -= static_cast<T>(rhs.x);
		y -= static_cast<T>(rhs.y);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>& Vec<2, T>::operator*= (U rhs)
	{
		x *= static_cast<T>(rhs);
		y *= static_cast<T>(rhs);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>& Vec<2, T>::operator*= (const Vec<1, U>& rhs)
	{
		x *= static_cast<T>(rhs[0]);
		y *= static_cast<T>(rhs[0]);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>& Vec<2, T>::operator*= (const Vec<2, U>& rhs)
	{
		x *= static_cast<T>(rhs.x);
		y *= static_cast<T>(rhs.y);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>& Vec<2, T>::operator/= (U rhs)
	{
		x /= static_cast<T>(rhs);
		y /= static_cast<T>(rhs);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>& Vec<2, T>::operator/= (const Vec<1, U>& rhs)
	{
		x /= static_cast<T>(rhs[0]);
		y /= static_cast<T>(rhs[0]);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<2, T>& Vec<2, T>::operator/= (const Vec<2, U>& rhs)
	{
		x /= static_cast<T>(rhs.x);
		y /= static_cast<T>(rhs.y);
		return *this;
	}

	// Vec3 ---------------------------------------------
	// --------------------------------------------------
	template <typename T>
	inline constexpr Vec<3, T>::Vec() : x(T()), y(T()), z(T()) {}

	template <typename T>
	inline constexpr Vec<3, T>::Vec(T n) : x(n), y(n), z(n) {}

	template <typename T>
	inline constexpr Vec<3, T>::Vec(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

	template <typename T>
	inline constexpr Vec<3, T>::Vec(const T* p) : x(p[0]), y(p[1]), z(p[2]) {}

	template <typename T>
	inline constexpr Vec<3, T>::Vec(const Vec<3, T>& src) : x(src.x), y(src.y), z(src.z) {}

	template <typename T>
	template <typename A, typename B, typename C>
	inline constexpr Vec<3, T>::Vec(A _x, B _y, C _z)
		: x(static_cast<T>(_x)), y(static_cast<T>(_y)), z(static_cast<T>(_z)) {}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>::Vec(const Vec<2, U>& src)
		: x(static_cast<T>(src.x)), y(static_cast<T>(src.y))
		, z(T()) {}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>::Vec(const Vec<3, U>& src)
		: x(static_cast<T>(src.x)), y(static_cast<T>(src.y))
		, z(static_cast<T>(src.z)) {}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>::Vec(const Vec<4, U>& src)
		: x(static_cast<T>(src.x)), y(static_cast<T>(src.y))
		, z(static_cast<T>(src.z)) {}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>::Vec(const Vec<Type::Dynamic, U>& v)
	{
		x = v.length() > 0 ? static_cast<T>(v[0]) : T();
		y = v.length() > 1 ? static_cast<T>(v[1]) : T();
		z = v.length() > 2 ? static_cast<T>(v[2]) : T();
	}

	template <typename T>
	inline constexpr T& Vec<3, T>::operator[] (size_t i)
	{
		if (i < 0 || i >= 3)
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");
		return e[i];
	};

	template <typename T>
	inline constexpr const T& Vec<3, T>::operator[] (size_t i) const
	{
		if (i < 0 || i >= 3) {
			int a = 0;
			a = a + a;
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");
		}
		return e[i];
	};

	template <typename T>
	inline constexpr T* Vec<3, T>::data()
	{
		return &e[0];
	};

	template <typename T>
	inline constexpr size_t Vec<3, T>::length() const
	{
		return 3;
	};

	template <typename T>
	inline constexpr Vec<2, T> Vec<3, T>::xy() const
	{
		return Vec<2, T>(x, y);
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<3, T>::rg() const
	{
		return Vec<2, T>(x, y);
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<3, T>::xz() const
	{
		return Vec<2, T>(x, z);
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<3, T>::rb() const
	{
		return Vec<2, T>(x, z);
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<3, T>::yz() const
	{
		return Vec<2, T>(y, z);
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<3, T>::gb() const
	{
		return Vec<2, T>(y, z);
	}

	template <typename T>
	inline constexpr Vec<3, T> Vec<3, T>::xyz() const
	{
		return Vec<3, T>(x, y, z);
	}

	template <typename T>
	inline constexpr Vec<3, T> Vec<3, T>::rgb() const
	{
		return Vec<3, T>(x, y, z);
	}

	template <typename T>
	inline constexpr Vec<3, T>& Vec<3, T>::operator++()
	{
		++x;
		++y;
		++z;
		return *this;
	}

	template <typename T>
	inline constexpr Vec<3, T>& Vec<3, T>::operator--()
	{
		--x;
		--y;
		--z;
		return *this;
	}

	template <typename T>
	inline constexpr Vec<3, T> Vec<3, T>::operator++(int)
	{
		Vec<3, T> res(*this);
		++* this;
		return res;
	}

	template <typename T>
	inline constexpr Vec<3, T> Vec<3, T>::operator--(int)
	{
		Vec<3, T> res(*this);
		--* this;
		return res;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>& Vec<3, T>::operator= (const Vec<3, U>& rhs)
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		z = static_cast<T>(rhs.z);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>& Vec<3, T>::operator+= (U rhs)
	{
		x += static_cast<T>(rhs);
		y += static_cast<T>(rhs);
		z += static_cast<T>(rhs);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>& Vec<3, T>::operator+= (const Vec<1, U>& rhs)
	{
		x += static_cast<T>(rhs[0]);
		y += static_cast<T>(rhs[0]);
		z += static_cast<T>(rhs[0]);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>& Vec<3, T>::operator+= (const Vec<3, U>& rhs)
	{
		x += static_cast<T>(rhs.x);
		y += static_cast<T>(rhs.y);
		z += static_cast<T>(rhs.z);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>& Vec<3, T>::operator-= (U rhs)
	{
		x -= static_cast<T>(rhs);
		y -= static_cast<T>(rhs);
		z -= static_cast<T>(rhs);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>& Vec<3, T>::operator-= (const Vec<1, U>& rhs)
	{
		x -= static_cast<T>(rhs[0]);
		y -= static_cast<T>(rhs[0]);
		z -= static_cast<T>(rhs[0]);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>& Vec<3, T>::operator-= (const Vec<3, U>& rhs)
	{
		x -= static_cast<T>(rhs.x);
		y -= static_cast<T>(rhs.y);
		z -= static_cast<T>(rhs.z);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>& Vec<3, T>::operator*= (U rhs)
	{
		x *= static_cast<T>(rhs);
		y *= static_cast<T>(rhs);
		z *= static_cast<T>(rhs);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>& Vec<3, T>::operator*= (const Vec<1, U>& rhs)
	{
		x *= static_cast<T>(rhs[0]);
		y *= static_cast<T>(rhs[0]);
		z *= static_cast<T>(rhs[0]);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>& Vec<3, T>::operator*= (const Vec<3, U>& rhs)
	{
		x *= static_cast<T>(rhs.x);
		y *= static_cast<T>(rhs.y);
		z *= static_cast<T>(rhs.z);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>& Vec<3, T>::operator/= (U rhs)
	{
		x /= static_cast<T>(rhs);
		y /= static_cast<T>(rhs);
		z /= static_cast<T>(rhs);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>& Vec<3, T>::operator/= (const Vec<1, U>& rhs)
	{
		x /= static_cast<T>(rhs[0]);
		y /= static_cast<T>(rhs[0]);
		z /= static_cast<T>(rhs[0]);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<3, T>& Vec<3, T>::operator/= (const Vec<3, U>& rhs)
	{
		x /= static_cast<T>(rhs.x);
		y /= static_cast<T>(rhs.y);
		z /= static_cast<T>(rhs.z);
		return *this;
	}

	// Vec4 ---------------------------------------------
	// --------------------------------------------------
	template <typename T>
	inline constexpr Vec<4, T>::Vec()
		: x(T()), y(T()), z(T()), w(T()) {}

	template <typename T>
	inline constexpr Vec<4, T>::Vec(T n) : x(n), y(n), z(n), w(n) {}

	template <typename T>
	inline constexpr Vec<4, T>::Vec(T _x, T _y, T _z, T _w)
		: x(_x), y(_y), z(_z), w(_w) {}

	template <typename T>
	inline constexpr Vec<4, T>::Vec(const T* p)
		: x(p[0]), y(p[1]), z(p[2]), w(p[3]) {}

	template <typename T>
	inline constexpr Vec<4, T>::Vec(const Vec<4, T>& src)
		: x(src.x), y(src.y), z(src.z), w(src.w) {}

	template <typename T>
	template <typename A, typename B, typename C, typename D>
	inline constexpr Vec<4, T>::Vec(A _x, B _y, C _z, D _w)
		: x(static_cast<T>(_x)), y(static_cast<T>(_y))
		, z(static_cast<T>(_z)), w(static_cast<T>(_w)) {}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>::Vec(const Vec<2, U>& src)
		: x(static_cast<T>(src.x)), y(static_cast<T>(src.y))
		, z(T()), w(T()) {}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>::Vec(const Vec<3, U>& src)
		: x(static_cast<T>(src.x)), y(static_cast<T>(src.y))
		, z(static_cast<T>(src.z)), w(T()) {}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>::Vec(const Vec<3, U>& src, U _w)
		: x(static_cast<T>(src.x)), y(static_cast<T>(src.y))
		, z(static_cast<T>(src.z)), w(_w) {}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>::Vec(const Vec<4, U>& src)
		: x(static_cast<T>(src.x)), y(static_cast<T>(src.y))
		, z(static_cast<T>(src.z)), w(static_cast<T>(src.w)) {}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>::Vec(const Vec<Type::Dynamic, U>& v)
	{
		x = v.length() > 0 ? static_cast<T>(v[0]) : T();
		y = v.length() > 1 ? static_cast<T>(v[1]) : T();
		z = v.length() > 2 ? static_cast<T>(v[2]) : T();
		w = v.length() > 3 ? static_cast<T>(v[3]) : T();
	}

	template <typename T>
	inline constexpr T& Vec<4, T>::operator[] (size_t i)
	{
		if (i < 0 || i >= 4)
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");
		return e[i];
	}

	template <typename T>
	inline constexpr const T& Vec<4, T>::operator[] (size_t i) const
	{
		if (i < 0 || i >= 4)
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");
		return e[i];
	}

	template <typename T>
	inline constexpr T* Vec<4, T>::data()
	{
		return &e[0];
	}

	template <typename T>
	inline constexpr size_t Vec<4, T>::length() const
	{
		return 4;
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<4, T>::xy() const
	{
		return Vec<2, T>(x, y);
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<4, T>::rg() const
	{
		return Vec<2, T>(x, y);
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<4, T>::xz() const
	{
		return Vec<2, T>(x, z);
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<4, T>::rb() const
	{
		return Vec<2, T>(x, z);
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<4, T>::yz() const
	{
		return Vec<2, T>(y, z);
	}

	template <typename T>
	inline constexpr Vec<2, T> Vec<4, T>::gb() const
	{
		return Vec<2, T>(y, z);
	}

	template <typename T>
	inline constexpr Vec<3, T> Vec<4, T>::xyz() const
	{
		return Vec<3, T>(x, y, z);
	}

	template <typename T>
	inline constexpr Vec<3, T> Vec<4, T>::rgb() const
	{
		return Vec<3, T>(x, y, z);
	}

	template <typename T>
	inline constexpr Vec<3, T> Vec<4, T>::xyw() const
	{
		return Vec<3, T>(x, y, w);
	}

	template <typename T>
	inline constexpr Vec<3, T> Vec<4, T>::rga() const
	{
		return Vec<3, T>(x, y, w);
	}

	template <typename T>
	inline constexpr Vec<4, T> Vec<4, T>::xyzw() const
	{
		return Vec<4, T>(x, y, z, w);
	}

	template <typename T>
	inline constexpr Vec<4, T> Vec<4, T>::rgba() const
	{
		return Vec<4, T>(x, y, z, w);
	}

	template <typename T>
	inline constexpr Vec<4, T>& Vec<4, T>::operator++()
	{
		++x;
		++y;
		++z;
		++w;
		return *this;
	}

	template <typename T>
	inline constexpr Vec<4, T>& Vec<4, T>::operator--()
	{
		--x;
		--y;
		--z;
		--w;
		return *this;
	}

	template <typename T>
	inline constexpr Vec<4, T> Vec<4, T>::operator++(int)
	{
		Vec<4, T> res(*this);
		++* this;
		return res;
	}

	template <typename T>
	inline constexpr Vec<4, T> Vec<4, T>::operator--(int)
	{
		Vec<4, T> res(*this);
		--* this;
		return res;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>& Vec<4, T>::operator= (const Vec<4, U>& rhs)
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		z = static_cast<T>(rhs.z);
		w = static_cast<T>(rhs.w);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>& Vec<4, T>::operator+= (U rhs)
	{
		x += static_cast<T>(rhs);
		y += static_cast<T>(rhs);
		z += static_cast<T>(rhs);
		w += static_cast<T>(rhs);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>& Vec<4, T>::operator+= (const Vec<1, U>& rhs)
	{
		x += static_cast<T>(rhs[0]);
		y += static_cast<T>(rhs[0]);
		z += static_cast<T>(rhs[0]);
		w += static_cast<T>(rhs[0]);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>& Vec<4, T>::operator+= (const Vec<4, U>& rhs)
	{
		x += static_cast<T>(rhs.x);
		y += static_cast<T>(rhs.y);
		z += static_cast<T>(rhs.z);
		w += static_cast<T>(rhs.w);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>& Vec<4, T>::operator-= (U rhs)
	{
		x -= static_cast<T>(rhs);
		y -= static_cast<T>(rhs);
		z -= static_cast<T>(rhs);
		w -= static_cast<T>(rhs);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>& Vec<4, T>::operator-= (const Vec<1, U>& rhs)
	{
		x -= static_cast<T>(rhs[0]);
		y -= static_cast<T>(rhs[0]);
		z -= static_cast<T>(rhs[0]);
		w -= static_cast<T>(rhs[0]);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>& Vec<4, T>::operator-= (const Vec<4, U>& rhs)
	{
		x -= static_cast<T>(rhs.x);
		y -= static_cast<T>(rhs.y);
		z -= static_cast<T>(rhs.z);
		w -= static_cast<T>(rhs.w);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>& Vec<4, T>::operator*= (U rhs)
	{
		x *= static_cast<T>(rhs);
		y *= static_cast<T>(rhs);
		z *= static_cast<T>(rhs);
		w *= static_cast<T>(rhs);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>& Vec<4, T>::operator*= (const Vec<1, U>& rhs)
	{
		x *= static_cast<T>(rhs[0]);
		y *= static_cast<T>(rhs[0]);
		z *= static_cast<T>(rhs[0]);
		w *= static_cast<T>(rhs[0]);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>& Vec<4, T>::operator*= (const Vec<4, U>& rhs)
	{
		x *= static_cast<T>(rhs.x);
		y *= static_cast<T>(rhs.y);
		z *= static_cast<T>(rhs.z);
		w *= static_cast<T>(rhs.w);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>& Vec<4, T>::operator/= (U rhs)
	{
		x /= static_cast<T>(rhs);
		y /= static_cast<T>(rhs);
		z /= static_cast<T>(rhs);
		w /= static_cast<T>(rhs);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>& Vec<4, T>::operator/= (const Vec<1, U>& rhs)
	{
		x /= static_cast<T>(rhs[0]);
		y /= static_cast<T>(rhs[0]);
		z /= static_cast<T>(rhs[0]);
		w /= static_cast<T>(rhs[0]);
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<4, T>& Vec<4, T>::operator/= (const Vec<4, U>& rhs)
	{
		x /= static_cast<T>(rhs.x);
		y /= static_cast<T>(rhs.y);
		z /= static_cast<T>(rhs.z);
		w /= static_cast<T>(rhs.w);
		return *this;
	}

	// Vec Dynamic --------------------------------------
	// --------------------------------------------------
	template <typename T>
	inline constexpr Vec<Type::Dynamic, T>::Vec()
		: len(0)
	{
		e = nullptr;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T>::Vec(size_t size)
		: len(size)
	{
		e = new T[size];
		for (size_t i = 0; i < size; ++i)
			e[i] = T(0);
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T>::Vec(size_t size, T n)
	{
		e = new T[size];
		for (size_t i = 0; i < size; ++i)
			e[i] = n;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T>::Vec(size_t size, const T* p)
		: len(size)
	{
		e = new T[size];
		for (size_t i = 0; i < size; ++i)
			e[i] = p[i];
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T>::Vec(const Vec<Type::Dynamic, T>& src)
		: len(src.length())
	{
		e = new T[len];
		for (size_t i = 0; i < len; ++i)
			e[i] = src.e[i];
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>::Vec(const std::initializer_list<U>& l)
		: len(l.end() - l.begin())
	{
		auto it = l.begin();
		e = new T[len];
		for (size_t i = 0; i < len; ++i)
			e[i] = static_cast<T>(*it++);
	}

	template <typename T>
	template <size_t M, typename U>
	inline constexpr Vec<Type::Dynamic, T>::Vec(const Vec<M, U>& src)
		: len(M)
	{
		e = new T[len];
		for (size_t i = 0; i < M; ++i)
		{
			e[i] = static_cast<T>(src[i]);
		}
	}

	template <typename T>
	inline constexpr T& Vec<Type::Dynamic, T>::operator[] (size_t i)
	{
		if (i < 0 || i >= len)
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");
		return e[i];
	}

	template <typename T>
	inline constexpr const T& Vec<Type::Dynamic, T>::operator[] (size_t i) const
	{
		if (i < 0 || i >= len)
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");
		return e[i];
	}

	template <typename T>
	inline constexpr T* Vec<Type::Dynamic, T>::data()
	{
		return e;
	}

	template <typename T>
	inline constexpr size_t Vec<Type::Dynamic, T>::length() const
	{
		return len;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator++()
	{
		for (size_t i = 0; i < len; ++i)
			++e[i];
		return *this;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator--()
	{
		for (size_t i = 0; i < len; ++i)
			--e[i];
		return *this;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> Vec<Type::Dynamic, T>::operator++(int)
	{
		Vec<Type::Dynamic, T> res(*this);
		++* this;
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> Vec<Type::Dynamic, T>::operator--(int)
	{
		Vec<Type::Dynamic, T> res(*this);
		--* this;
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator= (const Vec<Type::Dynamic, T>& rhs)
	{
		if (len != rhs.length())
		{
			delete[] e;
			len = rhs.length();
			e = new T[len];
		}
		for (size_t i = 0; i < len; ++i)
		{
			e[i] = rhs.e[i];
		}
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator= (const Vec<Type::Dynamic, U>& rhs)
	{
		if (len != rhs.length())
		{
			delete[] e;
			len = rhs.length();
			e = new T[len];
		}
		for (size_t i = 0; i < len; ++i)
		{
			e[i] = static_cast<T>(rhs.e[i]);
		}
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator+= (U rhs)
	{
		for (size_t i = 0; i < len; ++i)
		{
			e[i] += static_cast<T>(rhs);
		}
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator+= (const Vec<1, U>& rhs)
	{
		for (size_t i = 0; i < len; ++i)
		{
			e[i] += static_cast<T>(rhs.e[0]);
		}
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator+= (const Vec<Type::Dynamic, U>& rhs)
	{
		for (size_t i = 0; i < len; ++i)
		{
			if (i < rhs.length())
				e[i] += static_cast<T>(rhs.e[i]);
		}
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator-= (U rhs)
	{
		for (size_t i = 0; i < len; ++i)
		{
			e[i] -= static_cast<T>(rhs);
		}
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator-= (const Vec<1, U>& rhs)
	{
		for (size_t i = 0; i < len; ++i)
		{
			e[i] -= static_cast<T>(rhs.e[0]);
		}
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator-= (const Vec<Type::Dynamic, U>& rhs)
	{
		for (size_t i = 0; i < len; ++i)
		{
			if (i < rhs.length())
				e[i] -= static_cast<T>(rhs.e[i]);
		}
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator*= (U rhs)
	{
		for (size_t i = 0; i < len; ++i)
		{
			e[i] *= static_cast<T>(rhs);
		}
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator*= (const Vec<1, U>& rhs)
	{
		for (size_t i = 0; i < len; ++i)
		{
			e[i] *= static_cast<T>(rhs.e[0]);
		}
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator*= (const Vec<Type::Dynamic, U>& rhs)
	{
		for (size_t i = 0; i < len; ++i)
		{
			if (i < rhs.length())
				e[i] *= static_cast<T>(rhs.e[i]);
		}
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator/= (U rhs)
	{
		for (size_t i = 0; i < len; ++i)
		{
			e[i] /= static_cast<T>(rhs);
		}
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator/= (const Vec<1, U>& rhs)
	{
		for (size_t i = 0; i < len; ++i)
		{
			e[i] /= static_cast<T>(rhs.e[0]);
		}
		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Vec<Type::Dynamic, T>& Vec<Type::Dynamic, T>::operator/= (const Vec<Type::Dynamic, U>& rhs)
	{
		for (size_t i = 0; i < len; ++i)
		{
			if (i < rhs.length())
				e[i] /= static_cast<T>(rhs.e[i]);
		}
		return *this;
	}

	// Vec operator STATIC ------------------------------
	// --------------------------------------------------
	template <size_t N, typename T>
	inline constexpr Vec<N, T> operator-(const Vec<N, T>& rhs)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i) {
			res[i] = -rhs[i];
		}
		return res;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> operator+(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i) {
			res[i] = lhs[i] + rhs[i];
		}
		return res;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> operator-(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i) {
			res[i] = lhs[i] - rhs[i];
		}
		return res;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> operator+(const Vec<N, T>& lhs, T rhs)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i) {
			res[i] = lhs[i] + rhs;
		}
		return res;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> operator-(const Vec<N, T>& lhs, T rhs)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i) {
			res[i] = lhs[i] - rhs;
		}
		return res;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> operator+(T lhs, const Vec<N, T>& rhs)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i) {
			res[i] = lhs + rhs[i];
		}
		return res;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> operator-(T lhs, const Vec<N, T>& rhs)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i) {
			res[i] = lhs - rhs[i];
		}
		return res;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> operator*(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i) {
			res[i] = lhs[i] * rhs[i];
		}
		return res;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> operator/(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i) {
			res[i] = lhs[i] / rhs[i];
		}
		return res;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> operator*(const Vec<N, T>& lhs, T rhs)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i) {
			res[i] = lhs[i] * rhs;
		}
		return res;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> operator/(const Vec<N, T>& lhs, T rhs)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i) {
			res[i] = lhs[i] / rhs;
		}
		return res;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> operator*(T lhs, const Vec<N, T>& rhs)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i) {
			res[i] = lhs * rhs[i];
		}
		return res;
	}

	template <size_t N, typename T>
	inline constexpr Vec<N, T> operator/(T lhs, const Vec<N, T>& rhs)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i) {
			res[i] = lhs / rhs[i];
		}
		return res;
	}

	template <size_t N, typename T, typename U>
	inline constexpr bool operator==(const Vec<N, T>& lhs, const Vec<N, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template <size_t N, typename T, typename U>
	inline constexpr bool operator!=(const Vec<N, T>& lhs, const Vec<N, U>& rhs)
	{
		return !(lhs == rhs);
	}

	template <size_t N, typename T>
	inline std::ostream& operator<<(std::ostream& os, const Vec<N, T>& rhs)
	{
		os << "[ ";
		for (size_t i = 0; i < N; ++i)
		{
			os << rhs[i];
			if (i < N - 1)
				os << ", ";
		}
		os << " ]";
		return os;
	}

	// Vec operator DYNAMIC -----------------------------
	// --------------------------------------------------
	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> operator-(const Vec<Type::Dynamic, T>& rhs)
	{
		Vec<Type::Dynamic, T> res(rhs);
		for (size_t i = 0; i < res.length(); ++i) {
			res[i] = -rhs[i];
		}
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> operator+(const Vec<Type::Dynamic, T>& lhs, const Vec<Type::Dynamic, T>& rhs)
	{
		Vec<Type::Dynamic, T> res(lhs);
		res += rhs;
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> operator-(const Vec<Type::Dynamic, T>& lhs, const Vec<Type::Dynamic, T>& rhs)
	{
		Vec<Type::Dynamic, T> res(lhs);
		res -= rhs;
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> operator+(const Vec<Type::Dynamic, T>& lhs, T rhs)
	{
		Vec<Type::Dynamic, T> res(lhs);
		res += rhs;
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> operator-(const Vec<Type::Dynamic, T>& lhs, T rhs)
	{
		Vec<Type::Dynamic, T> res(lhs);
		res -= rhs;
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> operator+(T lhs, const Vec<Type::Dynamic, T>& rhs)
	{
		Vec<Type::Dynamic, T> res(rhs);
		res += lhs;
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> operator-(T lhs, const Vec<Type::Dynamic, T>& rhs)
	{
		Vec<Type::Dynamic, T> res(rhs);
		res = -res;
		res += lhs;
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> operator*(const Vec<Type::Dynamic, T>& lhs, const Vec<Type::Dynamic, T>& rhs)
	{
		Vec<Type::Dynamic, T> res(lhs);
		res *= rhs;
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> operator/(const Vec<Type::Dynamic, T>& lhs, const Vec<Type::Dynamic, T>& rhs)
	{
		Vec<Type::Dynamic, T> res(lhs);
		res /= rhs;
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> operator*(const Vec<Type::Dynamic, T>& lhs, T rhs)
	{
		Vec<Type::Dynamic, T> res(lhs);
		res *= rhs;
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> operator/(const Vec<Type::Dynamic, T>& lhs, T rhs)
	{
		Vec<Type::Dynamic, T> res(lhs);
		res /= rhs;
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> operator*(T lhs, const Vec<Type::Dynamic, T>& rhs)
	{
		Vec<Type::Dynamic, T> res(rhs);
		for (size_t i = 0; i < res.length(); ++i) {
			res[i] = lhs * rhs[i];
		}
		return res;
	}

	template <typename T>
	inline constexpr Vec<Type::Dynamic, T> operator/(T lhs, const Vec<Type::Dynamic, T>& rhs)
	{
		Vec<Type::Dynamic, T> res(rhs);
		for (size_t i = 0; i < res.length(); ++i) {
			res[i] = lhs / rhs[i];
		}
		return res;
	}

	template <typename T, typename U>
	inline constexpr bool operator==(const Vec<Type::Dynamic, T>& lhs, const Vec<Type::Dynamic, U>& rhs)
	{
		if (lhs.length() != rhs.length())
			return false;
		for (size_t i = 0; i < lhs.length(); ++i)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template <typename T>
	inline std::ostream& operator<<(std::ostream& os, const Vec<Type::Dynamic, T>& rhs)
	{
		os << "[ ";
		for (size_t i = 0; i < rhs.length(); ++i)
		{
			os << rhs[i];
			if (i < rhs.length() - 1)
				os << ", ";
		}
		os << " ]";
		return os;
	}
} // namespace MiniRenderer