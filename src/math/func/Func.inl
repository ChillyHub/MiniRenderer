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
	template <typename T> inline T Sqrt(T a) { return std::sqrt(a); }

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
			return Vec<N, T>(T(0));
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

	template <typename T>
	inline Vec<Type::Dynamic, T> Abs(const Vec<Type::Dynamic, T>& a)
	{
		Vec<Type::Dynamic, T> res(a.length());
		for (size_t i = 0; i < a.length(); ++i)
		{
			res[i] = std::abs(a[i]);
		}
		return res;
	}

	template <typename T>
	inline Vec<Type::Dynamic, T> Min(const Vec<Type::Dynamic, T>& a, const Vec<Type::Dynamic, T>& b)
	{
		if (a.length() != b.length())
			throw std::runtime_error(S("ERROR: [") + __func__ + "] Vectors length not equals");
		
		Vec<Type::Dynamic, T> res(a.length());
		for (size_t i = 0; i < a.length(); ++i)
		{
			res[i] = std::min(a[i], b[i]);
		}
		return res;
	}

	template <typename T>
	inline Vec<Type::Dynamic, T> Max(const Vec<Type::Dynamic, T>& a, const Vec<Type::Dynamic, T>& b)
	{
		if (a.length() != b.length())
			throw std::runtime_error(S("ERROR: [") + __func__ + "] Vectors length not equals");
		
		Vec<Type::Dynamic, T> res(a.length());
		for (size_t i = 0; i < a.length(); ++i)
		{
			res[i] = std::max(a[i], b[i]);
		}
		return res;
	}

	template <typename T, typename U>
	inline Vec<Type::Dynamic, T> Min(const Vec<Type::Dynamic, T>& a, U b)
	{
		Vec<Type::Dynamic, T> res(a.length());
		for (size_t i = 0; i < a.length(); ++i)
		{
			res[i] = std::min(a[i], static_cast<T>(b));
		}
		return res;
	}

	template <typename T, typename U>
	inline Vec<Type::Dynamic, T> Max(const Vec<Type::Dynamic, T>& a, U b)
	{
		Vec<Type::Dynamic, T> res(a.length());
		for (size_t i = 0; i < a.length(); ++i)
		{
			res[i] = std::max(a[i], static_cast<T>(b));
		}
		return res;
	}

	template <typename T, typename U>
	inline Vec<Type::Dynamic, T> Min(U a, const Vec<Type::Dynamic, T>& b)
	{
		Vec<Type::Dynamic, T> res(b.length());
		for (size_t i = 0; i < b.length(); ++i)
		{
			res[i] = std::min(static_cast<T>(a), b[i]);
		}
		return res;
	}

	template <typename T, typename U>
	inline Vec<Type::Dynamic, T> Max(U a, const Vec<Type::Dynamic, T>& b)
	{
		Vec<Type::Dynamic, T> res(b.length());
		for (size_t i = 0; i < b.length(); ++i)
		{
			res[i] = std::max(static_cast<T>(a), b[i]);
		}
		return res;
	}

	template <typename T>
	inline Vec<Type::Dynamic, T> Normailzed(const Vec<Type::Dynamic, T>& a)
	{
		auto norm = Norm(a);
		if (norm == 0)
			return Vec<Type::Dynamic, T>(a.length());
		return a / norm;
	}

	template <typename T>
	inline T Norm2(const Vec<Type::Dynamic, T>& a)
	{
		T sum = T();
		for (size_t i = 0; i < a.length(); ++i)
			sum += a[i] * a[i];
		return sum;
	}

	template <typename T>
	inline Vec<Type::Dynamic, T> Floor(const Vec<Type::Dynamic, T>& a)
	{
		Vec<Type::Dynamic, T> res(a.length());
		for (size_t i = 0; i < a.length(); ++i)
			res[i] = std::floor(a[i]);
		return res;
	}

	template <typename T>
	inline Vec<Type::Dynamic, T> Ceil(const Vec<Type::Dynamic, T>& a)
	{
		Vec<Type::Dynamic, T> res(a.length());
		for (size_t i = 0; i < a.length(); ++i)
			res[i] = std::ceil(a[i]);
		return res;
	}

	template <typename T>
	inline T Dot(const Vec<Type::Dynamic, T>& a, const Vec<Type::Dynamic, T>& b)
	{
		if (a.length() != b.length())
			throw std::runtime_error(S("ERROR: [") + __func__ + "] Vectors length not equals");
		
		T sum = T();
		for (size_t i = 0; i < a.length(); ++i)
			sum += a[i] * b[i];
		return sum;
	}

	template <typename T>
	inline T Cross(const Vec<Type::Dynamic, T>& a, const Vec<Type::Dynamic, T>& b)
	{
		if (a.length() == 2 && b.length() == 2)
			return Cross(Vec<2, T>(a), Vec<2, T>(b));
		if (a.length() == 3 && b.length() == 3)
			return Cross(Vec<3, T>(a), Vec<3, T>(b));
		if (a.length() == 4 && b.length() == 4)
			return Cross(Vec<4, T>(a), Vec<4, T>(b));
		
		throw std::runtime_error(S("ERROR: [") + __func__ + "] Vectors length not match");
		return T();
	}

	// Matrix ------------------------------------------------------
	// -------------------------------------------------------------
	template <size_t N, typename T>
	inline Mat<N, 1, T> Transpose(const Vec<N, T>& a)
	{
		Mat<N, 1, T> res;
		for (size_t i = 0; i < N; ++i)
			res[0][i] = a[i];
		return res;
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

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> Transpose(const Vec<Type::Dynamic, T>& a)
	{
		const size_t N = a.length();

		Mat<Type::Dynamic, Type::Dynamic, T> res(N, 1);
		for (size_t i = 0; i < N; ++i)
			res[0][i] = a[i];
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> Transpose(const Mat<Type::Dynamic, Type::Dynamic, T>& a)
	{
		const size_t M = a.col_len(), N = a.row_len();
		
		Mat<Type::Dynamic, Type::Dynamic, T> res(N, M);
		for (size_t i = 0; i < M; ++i)
			for (size_t j = 0; j < N; ++j)
				res[i][j] = a[j][i];
		return res;
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

	Quat MatToQuat(const Mat3& a)
	{
		Quat q;

		float fourWSquaredMinus1 = a[0][0] + a[1][1] + a[2][2];
		float fourXSquaredMinus1 = a[0][0] - a[1][1] - a[2][2];
		float fourYSquaredMinus1 = a[1][1] - a[0][0] - a[2][2];
		float fourZSquaredMinus1 = a[2][2] - a[0][0] - a[1][1];

		int biggestIndex = 0;
		float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
		if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex = 1;
		}
		else if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex = 2;
		}
		else if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex = 3;
		}

		float biggestVal = Sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
		float mult = 0.25f / biggestVal;

		switch (biggestIndex)
		{
		case 0:
			q.w = biggestVal;
			q.x = (a[1][2] - a[2][1]) * mult;
			q.y = (a[2][0] - a[0][2]) * mult;
			q.z = (a[0][1] - a[1][0]) * mult;
			break;
		case 1:
			q.x = biggestVal;
			q.w = (a[1][2] - a[2][1]) * mult;
			q.y = (a[0][1] + a[1][0]) * mult;
			q.z = (a[2][0] + a[0][2]) * mult;
			break;
		case 2:
			q.y = biggestVal;
			q.w = (a[2][0] - a[0][2]) * mult;
			q.x = (a[0][1] + a[1][0]) * mult;
			q.z = (a[1][2] + a[2][1]) * mult;
			break;
		case 3:
			q.z = biggestVal;
			q.w = (a[0][1] - a[1][0]) * mult;
			q.x = (a[2][0] + a[0][2]) * mult;
			q.y = (a[1][2] + a[2][1]) * mult;
			break;
		default:
			break;
		}

		return q;
	}

	Quat MatToQuat(const Mat4& a)
	{
		return MatToQuat(Mat3(a));
	}
}