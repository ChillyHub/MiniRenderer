#pragma once

#include "Func.h"

namespace MiniRenderer::Math
{
	// Number ------------------------------------------------------
	// -------------------------------------------------------------
	template <typename T> inline T Abs(T a) { return std::abs(a); }
	template <typename T> inline T Min(T a, T b) { return std::min(a, b); }
	template <typename T> inline T Max(T a, T b) { return std::max(a, b); }
	template <typename T> inline T Floor(T a) { return std::floor(a); }
	template <typename T> inline T Ceil(T a) { return std::ceil(a); }
	template <typename T> inline T Lerp(T a, T b, float t) 
	{ 
		return std::lerp(a, b, t); 
	}
	template <typename T> inline T Lerp(T a, T b, double t) 
	{ 
		return std::lerp(a, b, t); 
	}
	template <typename T> inline T Clamp(T a, int min, int max)
	{
		return std::min(std::max(a, min), max);
	}
	template <typename T> inline T Clamp(T a, float min, float max)
	{
		return std::min(std::max(a, min), max);
	}
	template <typename T> inline T Clamp(T a, double min, double max)
	{
		return std::min(std::max(a, min), max);
	}

	template <typename T> inline T Sin(T a) { return std::sin(a); }
	template <typename T> inline T Cos(T a) { return std::cos(a); }
	template <typename T> inline T Tan(T a) { return std::tan(a); }
	template <typename T> inline T Cot(T a) { return std::tan(PI / 2.0f - a); }
	template <typename T> inline T Exp(T a) { return std::exp(a); }
	template <typename T> inline T Log(T a) { return std::log(a); }
	template <typename T> inline T Pow(T a, float p) { return std::pow(a, p); }

	template <typename T> inline T Asin(T a) { return std::asin(a); }
	template <typename T> inline T Acos(T a) { return std::acos(a); }
	template <typename T> inline T Atan(T a) { return std::atan(a); }
	template <typename T> inline T Atan2(T a, T b) { return std::atan2(a, b); }

	template <typename T> inline T Radians(T a) { return a * T(d_PI) / T(180); }
	template <typename T> inline T Degrees(T a) { return a / T(d_PI) * T(180); }

	// Vector ------------------------------------------------------
	// -------------------------------------------------------------
	template <size_t N, typename T>
	inline Vec<N, T> Abs(const Vec<N, T>& a)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i)
		{
			res[i] = std::abs(a[i]);
		}
		return res;
	}

	template <size_t N, typename T>
	inline Vec<N, T> Min(const Vec<N, T>& a, const Vec<N, T>& b)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i)
		{
			res[i] = std::min(a[i], b[i]);
		}
		return res;
	}

	template <size_t N, typename T>
	inline Vec<N, T> Max(const Vec<N, T>& a, const Vec<N, T>& b)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i)
		{
			res[i] = std::max(a[i], b[i]);
		}
		return res;
	}

	template <size_t N, typename T, typename U>
	inline Vec<N, T> Min(const Vec<N, T>& a, U b)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i)
		{
			res[i] = std::min(a[i], static_cast<T>(b));
		}
		return res;
	}

	template <size_t N, typename T, typename U>
	inline Vec<N, T> Max(const Vec<N, T>& a, U b)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i)
		{
			res[i] = std::max(a[i], static_cast<T>(b));
		}
		return res;
	}

	template <size_t N, typename T, typename U>
	inline Vec<N, T> Min(U a, const Vec<N, T>& b)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i)
		{
			res[i] = std::min(static_cast<T>(a), b[i]);
		}
		return res;
	}

	template <size_t N, typename T, typename U>
	inline Vec<N, T> Max(U a, const Vec<N, T>& b)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i)
		{
			res[i] = std::max(static_cast<T>(a), b[i]);
		}
		return res;
	}

	template <size_t N, typename T>
	inline Vec<N, T> Normailzed(const Vec<N, T>& a)
	{
		auto norm = Norm(a);
		if (norm == 0)
			return Vec<N, T>(0);
		return a / norm;
	}

	template <size_t N, typename T>
	inline T Norm(const Vec<N, T>& a)
	{
		return std::sqrt(Norm2(a));
	}

	template <size_t N, typename T>
	inline T Norm2(const Vec<N, T>& a)
	{
		T sum = T();
		for (size_t i = 0; i < N; ++i)
			sum += a[i] * a[i];
		return sum;
	}

	template <size_t N, typename T>
	inline Vec<N, T> Floor(const Vec<N, T>& a)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = std::floor(a[i]);
		return res;
	}

	template <size_t N, typename T>
	inline Vec<N, T> Ceil(const Vec<N, T>& a)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = std::ceil(a[i]);
		return res;
	}

	template <size_t N, typename T>
	inline T Dot(const Vec<N, T>& a, const Vec<N, T>& b)
	{
		T sum = T();
		for (size_t i = 0; i < N; ++i)
			sum += a[i] * b[i];
		return sum;
	}

	template <typename T>
	inline T Cross(const Vec<2, T>& a, const Vec<2, T>& b)
	{
		return a.x * b.y - a.y * b.x;
	}

	template <typename T>
	inline Vec<3, T> Cross(const Vec<3, T>& a, const Vec<3, T>& b)
	{
		return Vec<3, T>(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	template <typename T>
	inline Vec<4, T> Cross(const Vec<4, T>& a, const Vec<4, T>& b)
	{
		return Vec<4, T>(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, a.w);
	}

	template <size_t N, typename T>
	inline Vec<N, T> Lerp(const Vec<N, T>& a, const Vec<N, T>& b, float t)
	{
		return a + (b - a) * t;
	}

	template <size_t N, typename T>
	inline Vec<N, T> Lerp(const Vec<N, T>& a, const Vec<N, T>& b, double t)
	{
		return a + (b - a) * t;
	}

	template <size_t N, typename T>
	inline Vec<N, T> Clamp(const Vec<N, T>& a, float min, float max)
	{
		return Min(Max(a, min), max);
	}

	template <size_t N, typename T>
	inline Vec<N, T> Clamp(const Vec<N, T>& a,
		const Vec<N, T>& min, const Vec<N, T>& max)
	{
		return Min(Max(a, min), max);
	}

	template <typename T> inline T Saturate(const T& a)
	{
		return Clamp(a, 0.0f, 1.0f);
	}

	// Matrix ------------------------------------------------------
	// -------------------------------------------------------------
	template <typename T>
	inline T Det(const Mat<1, 1, T>& a)
	{
		return a[0][0];
	}

	template <typename T>
	inline T Det(const Mat<2, 2, T>& a)
	{
		return a[0][0] * a[1][1] - a[0][1] * a[1][0];
	}

	template <size_t N, typename T>
	inline T Det(const Mat<N, N, T>& a)
	{
		T sum = T();
		for (size_t i = 0; i < N; ++i)
			sum += a[0][i] * Cofactor(a, i, 0);
		return sum;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<N, M, T> Transpose(const Mat<M, N, T>& a)
	{
		Mat<N, M, T> res;
		for (size_t i = 0; i < M; ++i)
			for (size_t j = 0; j < N; ++j)
				res[i][j] = a[j][i];
		return res;
	}

	template <size_t N, typename T>
	inline Mat<N, N, T> Inverse(const Mat<N, N, T>& a)
	{
		return Adjugate(a) / Det(a);
	}

	template <size_t M, size_t N, typename T>
	inline T Cofactor(const Mat<M, N, T>& src, size_t m, size_t n)
	{
		assert(m < M && n < N);
		Mat<M - 1, N - 1, T> res;
		size_t i = 0;
		for (size_t a = 0; a < N; ++a)
		{
			size_t j = 0;
			if (a == n)
				continue;
			for (size_t b = 0; b < M; ++b)
			{
				if (b == m)
					continue;
				res[i][j] = src[a][b];
				++j;
			}
			++i;
		}
		return ((m + n) % 2 ? -1 : 1) * Det(res);
	}

	template <size_t M, size_t N, typename T>
	inline Mat<N, M, T> Adjugate(const Mat<M, N, T>& a)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			for (size_t j = 0; j < M; ++j)
				res[i][j] = Cofactor(a, j, i);
		return Transpose(res);
	}

	// Quaternion --------------------------------------------------
	// -------------------------------------------------------------
	Quat Exp(const Quat& a)
	{
		auto norm = a.norm();
		if (norm <= 0.00001f)
			return Quat();
		auto n = a / norm;
		return Quat{ Cos(norm), Sin(norm) * n.i, Sin(norm) * n.j, Sin(norm) * n.k };
	}

	Quat Log(const Quat& a)
	{
		auto n = Normailzed(a);
		auto alpha = Acos(n.w);
		return Quat{ 0.0f, alpha * n.i, alpha * n.j, alpha * n.k };
	}

	Quat Pow(const Quat& a, float p)
	{
		return Exp(p * Log(a));
	}

	Quat Normailzed(const Quat& a)
	{
		return a / a.norm();
	}

	float Norm(const Quat& a)
	{
		return a.norm();
	}

	float Norm2(const Quat& a)
	{
		return a.w * a.w + a.i * a.i + a.j * a.j + a.k * a.k;
	}

	float Dot(const Quat& a, const Quat& b)
	{
		return a.w * b.w + a.i * b.i + a.j * b.j + a.k * b.k;
	}

	Quat Lerp(const Quat& a, const Quat& b, float t)
	{
		auto aa = a;
		auto bb = b;
		auto dot = Dot(a, b);

		if (dot < 0.0f)
		{
			aa = -aa;
			dot = -dot;
		}

		float k0, k1;
		if (dot > 0.9999f)
		{
			k0 = 1.0f - t;
			k1 = t;
		}
		else
		{
			float sinab = std::sqrt(1.0f - dot * dot);
			float ab = std::atan2(sinab, dot);
			float sinab_i = 1.0f / sinab;

			k0 = std::sin((1.0f - t) * ab) * sinab_i;
			k1 = std::sin(t * ab) * sinab_i;
		}

		return aa * k0 + bb * k1;
	}

	Quat Conjugate(const Quat& a)
	{
		return a.conj();
	}

	Quat Inverse(const Quat& a)
	{
		return a.inverse();
	}
}