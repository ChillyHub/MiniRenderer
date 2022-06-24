#pragma once

#include "math/type/Base.h"
#include "math/type/Vec.h"
#include "math/type/Mat.h"
#include "math/type/Quat.h"

namespace MiniRenderer::Math
{
	// No.1
	template <size_t N, typename T>
	void LUDecompose(const Mat<N, N, T>& A, Mat<N, N, T>& L, Mat<N, N, T>& U);

	template <typename T>
	void LUDecompose(const Mat<Type::Dynamic, Type::Dynamic, T> & A, 
		Mat<Type::Dynamic, Type::Dynamic, T>& L, Mat<Type::Dynamic, Type::Dynamic, T>& U);

	template <size_t N, typename T>
	void LUPDecompose(const Mat<N, N, T>& A, Mat<N, N, T>& L, Mat<N, N, T>& U, Mat<N, N, T>& P);

	template <typename T>
	void LUPDecompose(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& L, 
		Mat<Type::Dynamic, Type::Dynamic, T>& U, 
		Mat<Type::Dynamic, Type::Dynamic, T>& P);

	// No.2
	template <size_t M, size_t N, typename T>
	void QRDecompose(const Mat<M, N, T>& A, Mat<M, N, T>& Q, Mat<M, N, T>& R);

	template <typename T>
	void QRDecompose(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R);

	template <size_t M, size_t N, typename T>
	void QRDecompose1(const Mat<M, N, T>& A, Mat<M, N, T>& Q, Mat<M, N, T>& R);

	template <typename T>
	void QRDecompose1(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R);

	template <size_t M, size_t N, typename T>
	void QRDecompose2(const Mat<M, N, T>& A, Mat<M, N, T>& Q, Mat<M, N, T>& R);

	template <typename T>
	void QRDecompose2(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R);

	template <size_t M, size_t N, typename T>
	void QRDecompose3(const Mat<M, N, T>& A, Mat<M, N, T>& Q, Mat<M, N, T>& R);

	template <typename T>
	void QRDecompose3(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R);

	// No.3
	template <size_t N, typename T>
	Vec<N, T> CoefCharactPoly(const Mat<N, N, T>& A);

	template <typename T>
	Vec<Type::Dynamic, T> CoefCharactPoly(const Mat<Type::Dynamic, Type::Dynamic, T>& A);

	template <size_t N, typename T>
	Vec<N, T> Solve(const Mat<N, N, T>& A, const Vec<N, T>& b);

	template <typename T>
	Vec<Type::Dynamic, T> Solve(const Mat<Type::Dynamic, Type::Dynamic, T>& A, const Vec<Type::Dynamic, T>& b);

	template <size_t N, typename T>
	Vec<N, T> SolveLU(const Mat<N, N, T>& L, const Mat<N, N, T>& U, const Vec<N, T>& b);

	template <typename T>
	Vec<Type::Dynamic, T> SolveLU(const Mat<Type::Dynamic, Type::Dynamic, T>& L, 
		const Mat<Type::Dynamic, Type::Dynamic, T>& U,
		const Vec<Type::Dynamic, T>& b);

	template <size_t N, typename T>
	Vec<N, T> SolveLUP(const Mat<N, N, T>& A, const Vec<N, T>& b);

	template <typename T>
	Vec<Type::Dynamic, T> SolveLUP(const Mat<Type::Dynamic, Type::Dynamic, T>& A, const Vec<Type::Dynamic, T>& b);

	template <size_t N, typename T>
	Vec<N, T> SolveQR(const Mat<N, N, T>& A, const Vec<N, T>& b);

	template <typename T>
	Vec<Type::Dynamic, T> SolveQR(const Mat<Type::Dynamic, Type::Dynamic, T>& A, const Vec<Type::Dynamic, T>& b);

	// function
	template <size_t M, size_t N, typename T>
	T Cofactor(const Mat<M, N, T>& A, size_t m, size_t n);

	template <typename T>
	T Cofactor(const Mat<Type::Dynamic, Type::Dynamic, T>& A, size_t m, size_t n);

	template <size_t M, size_t N, typename T>
	Mat<N, M, T> Adjugate(const Mat<M, N, T>& A);

	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> Adjugate(const Mat<Type::Dynamic, Type::Dynamic, T>& A);

	template <size_t N, typename T>
	Vec<N, T> PrincipalMinors(const Mat<N, N, T>& A);

	template <typename T>
	Vec<Type::Dynamic, T> PrincipalMinors(const Mat<Type::Dynamic, Type::Dynamic, T>& A);

	template <typename T>
	T Det(const Mat<1, 1, T>& a);

	template <typename T>
	T Det(const Mat<2, 2, T>& a);

	template <typename T>
	T Det(const Mat<3, 3, T>& a);

	template <typename T>
	T Det(const Mat<4, 4, T>& a);

	template <size_t N, typename T>
	T Det(const Mat<N, N, T>& a);

	template <typename T>
	T Det(const Mat<Type::Dynamic, Type::Dynamic, T>& a);

	// correct
	template <size_t M, size_t N, typename T>
	bool IsSquareMat(const Mat<M, N, T>& A);

	template <typename T>
	bool IsSquareMat(const Mat<Type::Dynamic, Type::Dynamic, T>& A);

	template <size_t N, typename T>
	bool IsPositiveDefinite(const Mat<N, N, T>& A);

	template <typename T>
	bool IsPositiveDefinite(const Mat<Type::Dynamic, Type::Dynamic, T>& A);
}

// inline file
#include "Algorithm.inl"