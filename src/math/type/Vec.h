#pragma once

#include "Base.h"

#define MATH_SIMD

namespace MiniRenderer
{
	/////////////////////////////////////////////////////
	// Vector: Vec<N, T>, Vec2, Vec3, Vec4
	//---------------------------------------------------

	template <size_t N, typename T>
	struct Vec {
		T e[N];

		constexpr Vec();
		constexpr explicit Vec(T n);
		constexpr explicit Vec(const T* p);
		constexpr Vec(const Vec<N, T>& src);

		template <typename U>
		constexpr Vec(const std::initializer_list<U>& l);
		template <size_t M, typename U>
		constexpr explicit Vec(const Vec<M, U>& src);

		template <typename U>
		constexpr explicit Vec(const Vec<Type::Dynamic, U>& v);

		constexpr T& operator[] (size_t i);
		constexpr const T& operator[] (size_t i) const;

		constexpr T* data();
		constexpr size_t length() const;

		constexpr Vec<N, T>& operator++();
		constexpr Vec<N, T>& operator--();
		constexpr Vec<N, T> operator++(int);
		constexpr Vec<N, T> operator--(int);

		template <typename U>
		constexpr Vec<N, T>& operator= (const Vec<N, U>& rhs);
		template <typename U>
		constexpr Vec<N, T>& operator+= (U rhs);
		template <typename U>
		constexpr Vec<N, T>& operator+= (const Vec<N, U>& rhs);
		template <typename U>
		constexpr Vec<N, T>& operator-= (U rhs);
		template <typename U>
		constexpr Vec<N, T>& operator-= (const Vec<N, U>& rhs);
		template <typename U>
		constexpr Vec<N, T>& operator*= (U rhs);
		template <typename U>
		constexpr Vec<N, T>& operator*= (const Vec<N, U>& rhs);
		template <typename U>
		constexpr Vec<N, T>& operator/= (U rhs);
		template <typename U>
		constexpr Vec<N, T>& operator/= (const Vec<N, U>& rhs);
	};

	template <typename T>
	struct Vec<2, T> {
		union
		{
			struct { T x, y; };
			struct { T r, g; };
			struct { T u, v; };
			struct { T s, t; };
			T e[2];
		};

		constexpr Vec();
		constexpr Vec(T _x, T _y);
		constexpr explicit Vec(T n);
		constexpr explicit Vec(const T* p);
		constexpr Vec(const Vec<2, T>& src);

		template <typename A, typename B>
		constexpr Vec(A _x, B _y);
		template <typename U>
		constexpr Vec(const Vec<2, U>& src);
		template <typename U>
		constexpr Vec(const Vec<3, U>& src);
		template <typename U>
		constexpr Vec(const Vec<4, U>& src);

		template <typename U>
		constexpr explicit Vec(const Vec<Type::Dynamic, U>& v);

		constexpr T& operator[] (size_t i);
		constexpr const T& operator[] (size_t i) const;

		constexpr T* data();
		constexpr size_t length() const;

		constexpr Vec<2, T> xy() const;
		constexpr Vec<2, T> rg() const;
		constexpr Vec<2, T> uv() const;
		constexpr Vec<2, T> st() const;

		constexpr Vec<2, T>& operator++();
		constexpr Vec<2, T>& operator--();
		constexpr Vec<2, T> operator++(int);
		constexpr Vec<2, T> operator--(int);

		template <typename U>
		constexpr Vec<2, T>& operator= (const Vec<2, U>& rhs);
		template <typename U>
		constexpr Vec<2, T>& operator+= (U rhs);
		template <typename U>
		constexpr Vec<2, T>& operator+= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<2, T>& operator+= (const Vec<2, U>& rhs);
		template <typename U>
		constexpr Vec<2, T>& operator-= (U rhs);
		template <typename U>
		constexpr Vec<2, T>& operator-= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<2, T>& operator-= (const Vec<2, U>& rhs);
		template <typename U>
		constexpr Vec<2, T>& operator*= (U rhs);
		template <typename U>
		constexpr Vec<2, T>& operator*= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<2, T>& operator*= (const Vec<2, U>& rhs);
		template <typename U>
		constexpr Vec<2, T>& operator/= (U rhs);
		template <typename U>
		constexpr Vec<2, T>& operator/= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<2, T>& operator/= (const Vec<2, U>& rhs);
	};

	template <typename T>
	struct Vec<3, T> {
		union
		{
			struct { T x, y, z; };
			struct { T r, g, b; };
			T e[3];
		};

		constexpr Vec();
		constexpr explicit Vec(T n);
		constexpr Vec(T _x, T _y, T _z);
		constexpr explicit Vec(const T* p);
		constexpr Vec(const Vec<3, T>& src);

		template <typename A, typename B, typename C>
		constexpr Vec(A _x, B _y, C _z);
		template <typename U>
		constexpr explicit Vec(const Vec<2, U>& src);
		template <typename U>
		constexpr Vec(const Vec<3, U>& src);
		template <typename U>
		constexpr Vec(const Vec<4, U>& src);

		template <typename U>
		constexpr explicit Vec(const Vec<Type::Dynamic, U>& v);

		constexpr T& operator[] (size_t i);
		constexpr const T& operator[] (size_t i) const;

		constexpr T* data();
		constexpr size_t length() const;

		constexpr Vec<2, T> xy() const;
		constexpr Vec<2, T> rg() const;
		constexpr Vec<2, T> xz() const;
		constexpr Vec<2, T> rb() const;
		constexpr Vec<2, T> yz() const;
		constexpr Vec<2, T> gb() const;

		constexpr Vec<3, T> xyz() const;
		constexpr Vec<3, T> rgb() const;

		constexpr Vec<3, T>& operator++();
		constexpr Vec<3, T>& operator--();
		constexpr Vec<3, T> operator++(int);
		constexpr Vec<3, T> operator--(int);

		template <typename U>
		constexpr Vec<3, T>& operator= (const Vec<3, U>& rhs);
		template <typename U>
		constexpr Vec<3, T>& operator+= (U rhs);
		template <typename U>
		constexpr Vec<3, T>& operator+= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<3, T>& operator+= (const Vec<3, U>& rhs);
		template <typename U>
		constexpr Vec<3, T>& operator-= (U rhs);
		template <typename U>
		constexpr Vec<3, T>& operator-= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<3, T>& operator-= (const Vec<3, U>& rhs);
		template <typename U>
		constexpr Vec<3, T>& operator*= (U rhs);
		template <typename U>
		constexpr Vec<3, T>& operator*= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<3, T>& operator*= (const Vec<3, U>& rhs);
		template <typename U>
		constexpr Vec<3, T>& operator/= (U rhs);
		template <typename U>
		constexpr Vec<3, T>& operator/= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<3, T>& operator/= (const Vec<3, U>& rhs);
	};

	template <typename T>
	struct Vec<4, T> {
		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			T e[4];
		};

		constexpr Vec();
		constexpr explicit Vec(T n);
		constexpr Vec(T _x, T _y, T _z, T _w);
		constexpr explicit Vec(const T* p);
		constexpr Vec(const Vec<4, T>& src);

		template <typename A, typename B, typename C, typename D>
		constexpr Vec(A _x, B _y, C _z, D _w);
		template <typename U>
		constexpr explicit Vec(const Vec<2, U>& src);
		template <typename U>
		constexpr explicit Vec(const Vec<3, U>& src);
		template <typename U>
		constexpr explicit Vec(const Vec<3, U>& src, U _w);
		template <typename U>
		constexpr Vec(const Vec<4, U>& src);

		template <typename U>
		constexpr explicit Vec(const Vec<Type::Dynamic, U>& v);

		constexpr T& operator[] (size_t i);
		constexpr const T& operator[] (size_t i) const;

		constexpr T* data();
		constexpr size_t length() const;

		constexpr Vec<2, T> xy() const;
		constexpr Vec<2, T> rg() const;
		constexpr Vec<2, T> xz() const;
		constexpr Vec<2, T> rb() const;
		constexpr Vec<2, T> yz() const;
		constexpr Vec<2, T> gb() const;

		constexpr Vec<3, T> xyz() const;
		constexpr Vec<3, T> rgb() const;
		constexpr Vec<3, T> xyw() const;
		constexpr Vec<3, T> rga() const;
		constexpr Vec<4, T> xyzw() const;
		constexpr Vec<4, T> rgba() const;

		constexpr Vec<4, T>& operator++();
		constexpr Vec<4, T>& operator--();
		constexpr Vec<4, T> operator++(int);
		constexpr Vec<4, T> operator--(int);

		template <typename U>
		constexpr Vec<4, T>& operator= (const Vec<4, U>& rhs);
		template <typename U>
		constexpr Vec<4, T>& operator+= (U rhs);
		template <typename U>
		constexpr Vec<4, T>& operator+= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<4, T>& operator+= (const Vec<4, U>& rhs);
		template <typename U>
		constexpr Vec<4, T>& operator-= (U rhs);
		template <typename U>
		constexpr Vec<4, T>& operator-= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<4, T>& operator-= (const Vec<4, U>& rhs);
		template <typename U>
		constexpr Vec<4, T>& operator*= (U rhs);
		template <typename U>
		constexpr Vec<4, T>& operator*= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<4, T>& operator*= (const Vec<4, U>& rhs);
		template <typename U>
		constexpr Vec<4, T>& operator/= (U rhs);
		template <typename U>
		constexpr Vec<4, T>& operator/= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<4, T>& operator/= (const Vec<4, U>& rhs);
	};

	template <typename T>
	struct Vec<Type::Dynamic, T> {
		T* e;

	private:
		size_t len;

	public:
		~Vec() { if (e) delete[] e; }

	public:
		constexpr Vec();
		constexpr Vec(size_t size);
		constexpr Vec(size_t size, T n);
		constexpr explicit Vec(size_t size, const T* p);
		constexpr Vec(const Vec<Type::Dynamic, T>& src);

		template <typename U>
		constexpr Vec(const std::initializer_list<U>& l);
		template <size_t M, typename U>
		constexpr explicit Vec(const Vec<M, U>& src);

		constexpr T& operator[] (size_t i);
		constexpr const T& operator[] (size_t i) const;

		constexpr T* data();
		constexpr size_t length() const;

		constexpr Vec<Type::Dynamic, T>& operator++();
		constexpr Vec<Type::Dynamic, T>& operator--();
		constexpr Vec<Type::Dynamic, T> operator++(int);
		constexpr Vec<Type::Dynamic, T> operator--(int);

		constexpr Vec<Type::Dynamic, T>& operator= (const Vec<Type::Dynamic, T>& rhs);
		template <typename U>
		constexpr Vec<Type::Dynamic, T>& operator= (const Vec<Type::Dynamic, U>& rhs);
		template <typename U>
		constexpr Vec<Type::Dynamic, T>& operator+= (U rhs);
		template <typename U>
		constexpr Vec<Type::Dynamic, T>& operator+= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<Type::Dynamic, T>& operator+= (const Vec<Type::Dynamic, U>& rhs);
		template <typename U>
		constexpr Vec<Type::Dynamic, T>& operator-= (U rhs);
		template <typename U>
		constexpr Vec<Type::Dynamic, T>& operator-= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<Type::Dynamic, T>& operator-= (const Vec<Type::Dynamic, U>& rhs);
		template <typename U>
		constexpr Vec<Type::Dynamic, T>& operator*= (U rhs);
		template <typename U>
		constexpr Vec<Type::Dynamic, T>& operator*= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<Type::Dynamic, T>& operator*= (const Vec<Type::Dynamic, U>& rhs);
		template <typename U>
		constexpr Vec<Type::Dynamic, T>& operator/= (U rhs);
		template <typename U>
		constexpr Vec<Type::Dynamic, T>& operator/= (const Vec<1, U>& rhs);
		template <typename U>
		constexpr Vec<Type::Dynamic, T>& operator/= (const Vec<Type::Dynamic, U>& rhs);
	};

	typedef Vec<2, float> Vec2;
	typedef Vec<3, float> Vec3;
	typedef Vec<4, float> Vec4;
	typedef Vec<2, int> IVec2;
	typedef Vec<3, int> IVec3;
	typedef Vec<4, int> IVec4;
	typedef Vec<2, double> DVec2;
	typedef Vec<3, double> DVec3;
	typedef Vec<4, double> DVec4;
	typedef Vec<2, unsigned int> UVec2;
	typedef Vec<3, unsigned int> UVec3;
	typedef Vec<4, unsigned int> UVec4;

	typedef Vec<Type::Dynamic, float> VecX;
	typedef Vec<Type::Dynamic, int> IVecX;
	typedef Vec<Type::Dynamic, double> DVecX;
	typedef Vec<Type::Dynamic, unsigned int> UVecX;

	// Static type operator
	template <size_t N, typename T>
	constexpr Vec<N, T> operator+(const Vec<N, T>& rhs);
	template <size_t N, typename T>
	constexpr Vec<N, T> operator-(const Vec<N, T>& rhs);
	template <size_t N, typename T>
	constexpr Vec<N, T> operator+(const Vec<N, T>& lhs, const Vec<N, T>& rhs);
	template <size_t N, typename T>
	constexpr Vec<N, T> operator-(const Vec<N, T>& lhs, const Vec<N, T>& rhs);
	template <size_t N, typename T>
	constexpr Vec<N, T> operator+(const Vec<N, T>& lhs, T rhs);
	template <size_t N, typename T>
	constexpr Vec<N, T> operator-(const Vec<N, T>& lhs, T rhs);
	template <size_t N, typename T>
	constexpr Vec<N, T> operator+(T lhs, const Vec<N, T>& rhs);
	template <size_t N, typename T>
	constexpr Vec<N, T> operator-(T lhs, const Vec<N, T>& rhs);
	template <size_t N, typename T>
	constexpr Vec<N, T> operator*(const Vec<N, T>& lhs, const Vec<N, T>& rhs);
	template <size_t N, typename T>
	constexpr Vec<N, T> operator/(const Vec<N, T>& lhs, const Vec<N, T>& rhs);
	template <size_t N, typename T>
	constexpr Vec<N, T> operator*(const Vec<N, T>& lhs, T rhs);
	template <size_t N, typename T>
	constexpr Vec<N, T> operator/(const Vec<N, T>& lhs, T rhs);
	template <size_t N, typename T>
	constexpr Vec<N, T> operator*(T lhs, const Vec<N, T>& rhs);
	template <size_t N, typename T>
	constexpr Vec<N, T> operator/(T lhs, const Vec<N, T>& rhs);

	template <size_t N, typename T, typename U>
	constexpr bool operator==(const Vec<N, T>& lhs, const Vec<N, U>& rhs);
	template <size_t N, typename T, typename U>
	constexpr bool operator!=(const Vec<N, T>& lhs, const Vec<N, U>& rhs);

	template <size_t N, typename T>
	std::ostream& operator<<(std::ostream& os, const Vec<N, T>& rhs);

	// Dynamic type operator
	template <typename T>
	constexpr Vec<Type::Dynamic, T> operator-(const Vec<Type::Dynamic, T>& rhs);
	template <typename T>
	constexpr Vec<Type::Dynamic, T> operator+(const Vec<Type::Dynamic, T>& lhs, const Vec<Type::Dynamic, T>& rhs);
	template <typename T>
	constexpr Vec<Type::Dynamic, T> operator-(const Vec<Type::Dynamic, T>& lhs, const Vec<Type::Dynamic, T>& rhs);
	template <typename T>
	constexpr Vec<Type::Dynamic, T> operator+(const Vec<Type::Dynamic, T>& lhs, T rhs);
	template <typename T>
	constexpr Vec<Type::Dynamic, T> operator-(const Vec<Type::Dynamic, T>& lhs, T rhs);
	template <typename T>
	constexpr Vec<Type::Dynamic, T> operator+(T lhs, const Vec<Type::Dynamic, T>& rhs);
	template <typename T>
	constexpr Vec<Type::Dynamic, T> operator-(T lhs, const Vec<Type::Dynamic, T>& rhs);
	template <typename T>
	constexpr Vec<Type::Dynamic, T> operator*(const Vec<Type::Dynamic, T>& lhs, const Vec<Type::Dynamic, T>& rhs);
	template <typename T>
	constexpr Vec<Type::Dynamic, T> operator/(const Vec<Type::Dynamic, T>& lhs, const Vec<Type::Dynamic, T>& rhs);
	template <typename T>
	constexpr Vec<Type::Dynamic, T> operator*(const Vec<Type::Dynamic, T>& lhs, T rhs);
	template <typename T>
	constexpr Vec<Type::Dynamic, T> operator/(const Vec<Type::Dynamic, T>& lhs, T rhs);
	template <typename T>
	constexpr Vec<Type::Dynamic, T> operator*(T lhs, const Vec<Type::Dynamic, T>& rhs);
	template <typename T>
	constexpr Vec<Type::Dynamic, T> operator/(T lhs, const Vec<Type::Dynamic, T>& rhs);

	template <typename T, typename U>
	constexpr bool operator==(const Vec<Type::Dynamic, T>& lhs, const Vec<Type::Dynamic, U>& rhs);

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const Vec<Type::Dynamic, T>& rhs);
} // namespace MiniRenderer

// inline file
#include "Vec.inl"

#ifdef MATH_SIMD
	#include "Vec_simd.inl"
#endif // MATH_SIMD
