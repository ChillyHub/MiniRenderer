#pragma once

#include "Complex.h"

namespace MiniRenderer
{
	template <typename T>
	inline constexpr Complex<T>::Complex()
	{
		real = T();
		imag = T();
	}

	template <typename T>
	inline constexpr Complex<T>::Complex(T r)
	{
		real = r;
		imag = T();
	}

	template <typename T>
	inline constexpr Complex<T>::Complex(T r, T i)
	{
		real = r;
		imag = i;
	}

	template <typename T>
	inline constexpr Complex<T>::Complex(const Complex& src)
	{
		real = src.real;
		imag = src.imag;
	}

	template <typename T>
	inline constexpr Complex<T>& Complex<T>::operator++()
	{
		++real;
		return *this;
	}
	
	template <typename T>
	inline constexpr Complex<T>& Complex<T>::operator--()
	{
		--real;
		return *this;
	}
	
	template <typename T>
	inline constexpr Complex<T> Complex<T>::operator++(int)
	{
		Complex<T> res(*this);
		++* this;
		return res;
	}
	
	template <typename T>
	inline constexpr Complex<T> Complex<T>::operator--(int)
	{
		Complex<T> res(*this);
		--* this;
		return res;
	}

	template <typename T>
	inline constexpr Complex<T>& Complex<T>::operator=(T rhs)
	{
		real = rhs;
		imag = T();
		return *this;
	}
	
	template <typename T>
	inline constexpr Complex<T>& Complex<T>::operator=(const Complex<T>& rhs)
	{
		real = rhs.real;
		imag = rhs.imag;
		return *this;
	}
	
	template <typename T>
	inline constexpr Complex<T>& Complex<T>::operator+=(T rhs)
	{
		real += rhs;
		return *this;
	}
	
	template <typename T>
	inline constexpr Complex<T>& Complex<T>::operator+=(const Complex<T>& rhs)
	{
		real += rhs.real;
		imag += rhs.imag;
		return *this;
	}
	
	template <typename T>
	inline constexpr Complex<T>& Complex<T>::operator-=(T rhs)
	{
		real -= rhs;
		return *this;
	}
	
	template <typename T>
	inline constexpr Complex<T>& Complex<T>::operator-=(const Complex<T>& rhs)
	{
		real -= rhs.real;
		imag -= rhs.imag;
		return *this;
	}
	
	template <typename T>
	inline constexpr Complex<T>& Complex<T>::operator*=(T rhs)
	{
		real *= rhs;
		imag *= rhs;
		return *this;
	}
	
	template <typename T>
	inline constexpr Complex<T>& Complex<T>::operator*=(const Complex<T>& rhs)
	{
		auto r = real * rhs.real - imag * rhs.imag;
		auto i = real * rhs.imag + imag * rhs.real;
		real = r;
		imag = i;
		return *this;
	}
	
	template <typename T>
	inline constexpr Complex<T>& Complex<T>::operator/=(T rhs)
	{
		real /= rhs;
		imag /= rhs;
		return *this;
	}
	
	template <typename T>
	inline constexpr Complex<T>& Complex<T>::operator/=(const Complex<T>& rhs)
	{
		auto denom = rhs.real * rhs.real + rhs.imag * rhs.imag;
		auto r = (real * rhs.real + imag * rhs.imag) / denom;
		auto i = (imag * rhs.real - real * rhs.imag) / denom;
		real = r;
		imag = i;
		return *this;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator+(const Complex<T>& rhs)
	{
		return rhs;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator-(const Complex<T>& rhs)
	{
		Complex<T> res;
		res.real = -rhs.real;
		res.imag = -rhs.imag;
		return res;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator+(const Complex<T>& lhs, T rhs)
	{
		Complex<T> res;
		res.real = lhs.real + rhs;
		res.imag = lhs.imag;
		return res;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator+(T lhs, const Complex<T>& rhs)
	{
		Complex<T> res;
		res.real = rhs.real + lhs;
		res.imag = rhs.imag;
		return res;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator+(const Complex<T>& lhs, const Complex<T>& rhs)
	{
		Complex<T> res;
		res.real = lhs.real + rhs.real;
		res.imag = lhs.imag + rhs.imag;
		return res;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator-(const Complex<T>& lhs, T rhs)
	{
		Complex<T> res;
		res.real = lhs.real - rhs;
		res.imag = lhs.imag;
		return res;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator-(T lhs, const Complex<T>& rhs)
	{
		Complex<T> res;
		res.real = rhs.real - lhs;
		res.imag = rhs.imag;
		return res;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator-(const Complex<T>& lhs, const Complex<T>& rhs)
	{
		Complex<T> res;
		res.real = lhs.real - rhs.real;
		res.imag = lhs.imag - rhs.imag;
		return res;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator*(const Complex<T>& lhs, T rhs)
	{
		Complex<T> res;
		res.real = lhs.real * rhs;
		res.imag = lhs.imag * rhs;
		return res;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator*(T lhs, const Complex<T>& rhs)
	{
		Complex<T> res;
		res.real = rhs.real * lhs;
		res.imag = rhs.imag * rhs;
		return res;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator*(const Complex<T>& lhs, const Complex<T>& rhs)
	{
		Complex<T> res;
		res.real = lhs.real * rhs.real - lhs.imag * rhs.imag;
		res.imag = lhs.real * rhs.imag + lhs.imag * rhs.real;
		return res;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator/(const Complex<T>& lhs, T rhs)
	{
		Complex<T> res;
		res.real = lhs.real / rhs;
		res.imag = lhs.real / rhs;
		return res;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator/(T lhs, const Complex<T>& rhs)
	{
		Complex<T> res;
		auto denom = rhs.real * rhs.real + rhs.imag * rhs.imag;
		res.real = lhs * rhs.real / denom;
		res.imag = -lhs * rhs.imag / denom;
		return res;
	}
	
	template <typename T>
	inline constexpr Complex<T> operator/(const Complex<T>& lhs, const Complex<T>& rhs)
	{
		Complex<T> res;
		auto denom = rhs.real * rhs.real + rhs.imag * rhs.imag;
		res.real = (lhs.real * rhs.real + lhs.imag * rhs.imag) / denom;
		res.imag = (lhs.imag * rhs.real - lhs.real * rhs.imag) / denom;
		return res;
	}

	template <typename T, typename U>
	inline constexpr bool operator==(const Complex<T>& lhs, const Complex<U>& rhs)
	{
		return lhs.real == rhs.real && lhs.imag == rhs.imag;
	}

	template <typename T, typename U>
	inline constexpr bool operator!=(const Complex<T>& lhs, const Complex<U>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	inline std::ostream& operator<<(std::ostream& os, const Complex<T>& rhs)
	{
		os << "(" << rhs.real;
		if (rhs.imag < 0)
			os << " - " << -rhs.imag << "i)";
		else
			os << " + " << rhs.imag << "i)";
		return os;
	}
} // namespace MiniRenderer