#pragma once

#include "math/type/Base.h"
#include "math/type/Vec.h"
#include "math/type/Mat.h"
#include "math/type/Quat.h"

namespace MiniRenderer::Math
{
	// Number ------------------------------------------------------
	// -------------------------------------------------------------
	template <typename T> T Abs(T a);
	template <typename T> T Min(T a, T b);
	template <typename T> T Max(T a, T b);
	template <typename T> T Floor(T a);
	template <typename T> T Ceil(T a);
	template <typename T> T Lerp(T a, T b, float t);
	template <typename T> T Lerp(T a, T b, double t);
	template <typename T> T Clamp(T a, int min, int max);
	template <typename T> T Clamp(T a, float min, float max);
	template <typename T> T Clamp(T a, double min, double max);

	template <typename T> T Sin(T a);
	template <typename T> T Cos(T a);
	template <typename T> T Tan(T a);
	template <typename T> T Cot(T a);
	template <typename T> T Exp(T a);
	template <typename T> T Log(T a);
	template <typename T> T Pow(T a, float p);

	template <typename T> T Asin(T a);
	template <typename T> T Acos(T a);
	template <typename T> T Atan(T a);
	template <typename T> T Atan2(T a, T b);

	template <typename T> T Radians(T a);
	template <typename T> T Degrees(T a);
	
	// Vector ------------------------------------------------------
	// -------------------------------------------------------------
	template <size_t N, typename T>
	Vec<N, T> Abs(const Vec<N, T>& a);
	template <size_t N, typename T>
	Vec<N, T> Min(const Vec<N, T>& a, const Vec<N, T>& b);
	template <size_t N, typename T>
	Vec<N, T> Max(const Vec<N, T>& a, const Vec<N, T>& b);
	template <size_t N, typename T, typename U>
	Vec<N, T> Min(const Vec<N, T>& a, U b);
	template <size_t N, typename T, typename U>
	Vec<N, T> Max(const Vec<N, T>& a, U b);
	template <size_t N, typename T, typename U>
	Vec<N, T> Min(U a, const Vec<N, T>& b);
	template <size_t N, typename T, typename U>
	Vec<N, T> Max(U a, const Vec<N, T>& b);

	template <size_t N, typename T>
	Vec<N, T> Normailzed(const Vec<N, T>& a);

	template <size_t N, typename T>
	T Norm(const Vec<N, T>& a);
	template <size_t N, typename T>
	T Norm2(const Vec<N, T>& a);

	template <size_t N, typename T>
	Vec<N, T> Floor(const Vec<N, T>& a);
	template <size_t N, typename T>
	Vec<N, T> Ceil(const Vec<N, T>& a);

	template <size_t N, typename T>
	T Dot(const Vec<N, T>& a, const Vec<N, T>& b);
	template <typename T>
	T Cross(const Vec<2, T>& a, const Vec<2, T>& b);
	template <typename T>
	Vec<3, T> Cross(const Vec<3, T>& a, const Vec<3, T>& b);
	template <typename T>
	Vec<4, T> Cross(const Vec<4, T>& a, const Vec<4, T>& b);

	template <size_t N, typename T>
	Vec<N, T> Lerp(const Vec<N, T>& a, const Vec<N, T>& b, float t);
	template <size_t N, typename T>
	Vec<N, T> Lerp(const Vec<N, T>& a, const Vec<N, T>& b, double t);
	template <size_t N, typename T>
	Vec<N, T> Clamp(const Vec<N, T>& a, float min, float max);
	template <size_t N, typename T>
	Vec<N, T> Clamp(const Vec<N, T>& a,
		const Vec<N, T>& min, const Vec<N, T>& max);

	template <typename T> T Saturate(const T& a);

	// Matrix ------------------------------------------------------
	// -------------------------------------------------------------
	template <typename T>
	T Det(const Mat<1, 1, T>& a);
	template <typename T>
	T Det(const Mat<2, 2, T>& a);
	template <size_t N, typename T>
	T Det(const Mat<N, N, T>& a);
	template <size_t M, size_t N, typename T>
	Mat<N, M, T> Transpose(const Mat<M, N, T>& a);
	template <size_t N, typename T>
	Mat<N, N, T> Inverse(const Mat<N, N, T>& a);

	template <size_t M, size_t N, typename T>
	T Cofactor(const Mat<M, N, T>& src, size_t m, size_t n);
	template <size_t M, size_t N, typename T>
	Mat<N, M, T> Adjugate(const Mat<M, N, T>& a);

	// Quaternion --------------------------------------------------
	// -------------------------------------------------------------
	inline Quat Exp(const Quat& a);
	inline Quat Log(const Quat& a);
	inline Quat Pow(const Quat& a, float p);

	inline Quat Normailzed(const Quat& a);

	inline float Norm(const Quat& a);
	inline float Norm2(const Quat& a);
	inline float Dot(const Quat& a, const Quat& b);

	inline Quat Lerp(const Quat& a, const Quat& b, float t);
	inline Quat Conjugate(const Quat& a);
	inline Quat Inverse(const Quat& a);
}

// inline file
#include "Func.inl"