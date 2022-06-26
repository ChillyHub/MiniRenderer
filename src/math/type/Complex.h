#pragma once

#include "Base.h"

namespace MiniRenderer
{
	template <typename T>
	struct Complex
	{
		union
		{
			struct { T real, imag; };
			//T e[2];
		};

		constexpr Complex();
		constexpr Complex(T r);
		constexpr Complex(T r, T i);
		constexpr Complex(const Complex<T>& src);

		constexpr Complex<T>& operator++();
		constexpr Complex<T>& operator--();
		constexpr Complex<T> operator++(int);
		constexpr Complex<T> operator--(int);
		
		constexpr Complex<T>& operator=(T rhs);
		constexpr Complex<T>& operator=(const Complex<T>& rhs);
		constexpr Complex<T>& operator+=(T rhs);
		constexpr Complex<T>& operator+=(const Complex<T>& rhs);
		constexpr Complex<T>& operator-=(T rhs);
		constexpr Complex<T>& operator-=(const Complex<T>& rhs);
		constexpr Complex<T>& operator*=(T rhs);
		constexpr Complex<T>& operator*=(const Complex<T>& rhs);
		constexpr Complex<T>& operator/=(T rhs);
		constexpr Complex<T>& operator/=(const Complex<T>& rhs);
	};

	template <typename T>
	constexpr Complex<T> operator+(const Complex<T>& rhs);
	template <typename T>
	constexpr Complex<T> operator-(const Complex<T>& rhs);
	template <typename T>
	constexpr Complex<T> operator+(const Complex<T>& lhs, T rhs);
	template <typename T>
	constexpr Complex<T> operator+(T lhs, const Complex<T>& rhs);
	template <typename T>
	constexpr Complex<T> operator+(const Complex<T>& lhs, const Complex<T>& rhs);
	template <typename T>
	constexpr Complex<T> operator-(const Complex<T>& lhs, T rhs);
	template <typename T>
	constexpr Complex<T> operator-(T lhs, const Complex<T>& rhs);
	template <typename T>
	constexpr Complex<T> operator-(const Complex<T>& lhs, const Complex<T>& rhs);
	template <typename T>
	constexpr Complex<T> operator*(const Complex<T>& lhs, T rhs);
	template <typename T>
	constexpr Complex<T> operator*(T lhs, const Complex<T>& rhs);
	template <typename T>
	constexpr Complex<T> operator*(const Complex<T>& lhs, const Complex<T>& rhs);
	template <typename T>
	constexpr Complex<T> operator/(const Complex<T>& lhs, T rhs);
	template <typename T>
	constexpr Complex<T> operator/(T lhs, const Complex<T>& rhs);
	template <typename T>
	constexpr Complex<T> operator/(const Complex<T>& lhs, const Complex<T>& rhs);

	template <typename T, typename U>
	constexpr bool operator==(const Complex<T>& lhs, const Complex<U>& rhs);
	template <typename T, typename U>
	constexpr bool operator!=(const Complex<T>& lsh, const Complex<U>& rhs);

	template <typename T, typename U>
	constexpr bool operator<(const Complex<T>& lhs, U rhs);
	template <typename T, typename U>
	constexpr bool operator>(const Complex<T>& lhs, U rhs);

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const Complex<T>& rhs);

	typedef Complex<int> IComplex;
	typedef Complex<float> FComplex;
	typedef Complex<double> DComplex;
	typedef Complex<unsigned int> UComplex;
} // namespace MiniRenderer

// inline file
#include "Complex.inl"