#pragma once

#include "math/type/Base.h"
#include "math/type/Vec.h"
#include "math/type/Mat.h"
#include "math/type/Quat.h"

#include "math/func/Func.h"

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
	void QRDecompose(const Mat<M, N, T>& A, Mat<M, M, T>& Q, Mat<M, N, T>& R);

	template <typename T>
	void QRDecompose(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R);

	template <size_t M, size_t N, typename T>
	void QRDecompose_HouseholderReflection(const Mat<M, N, T>& A, Mat<M, M, T>& Q, Mat<M, N, T>& R);

	template <typename T>
	void QRDecompose_HouseholderReflection(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R);

	template <size_t M, size_t N, typename T>
	void QRDecompose_GivensRotation(const Mat<M, N, T>& A, Mat<M, M, T>& Q, Mat<M, N, T>& R);

	template <typename T>
	void QRDecompose_GivensRotation(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R);

	template <size_t M, size_t N, typename T>
	void QRDecompose_ModifiedGramSchmidtOrthogonalization(const Mat<M, N, T>& A, Mat<M, M, T>& Q, Mat<M, N, T>& R);

	template <typename T>
	void QRDecompose_ModifiedGramSchmidtOrthogonalization(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R);

	// No.3
	template <size_t N, typename T>
	Vec<N + 1, T> FindEigenByTridiagonalMat(const Mat<N, N, T>& A);

	template <typename T>
	Vec<Type::Dynamic, T> FindEigenByTridiagonalMat(const Mat<Type::Dynamic, Type::Dynamic, T>& A);

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
	Vec<N, T> SolveLUP(const Mat<N, N, T>& L, const Mat<N, N, T>& U, const Mat<N, N, T>& P, const Vec<N, T>& b);

	template <typename T>
	Vec<Type::Dynamic, T> SolveLUP(const Mat<Type::Dynamic, Type::Dynamic, T>& L, 
		const Mat<Type::Dynamic, Type::Dynamic, T>& U, 
		const Mat<Type::Dynamic, Type::Dynamic, T>& P, 
		const Vec<Type::Dynamic, T>& b);

	template <size_t N, typename T>
	Vec<N, T> SolveQR(const Mat<N, N, T>& Q, const Mat<N, N, T>& R, const Vec<N, T>& b);

	template <typename T>
	Vec<Type::Dynamic, T> SolveQR(const Mat<Type::Dynamic, Type::Dynamic, T>& Q, 
		const Mat<Type::Dynamic, Type::Dynamic, T>& R, const Vec<Type::Dynamic, T>& b);

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

	template <typename T>
	Mat<1, 1, T> Inverse(const Mat<1, 1, T>& a);

	template <typename T>
	Mat<2, 2, T> Inverse(const Mat<2, 2, T>& a);

	template <typename T>
	Mat<3, 3, T> Inverse(const Mat<3, 3, T>& a);

	template <typename T>
	Mat<4, 4, T> Inverse(const Mat<4, 4, T>& a);

	template <size_t N, typename T>
	Mat<N, N, T> Inverse(const Mat<N, N, T>& a);

	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> Inverse(const Mat<Type::Dynamic, Type::Dynamic, T>& a);

	// correct
	template <size_t M, size_t N, typename T>
	bool IsSquareMat(const Mat<M, N, T>& A);

	template <typename T>
	bool IsSquareMat(const Mat<Type::Dynamic, Type::Dynamic, T>& A);

	template <size_t M, size_t N, typename T>
	bool IsRegularMat(const Mat<M, N, T>& A);

	template <typename T>
	bool IsRegularMat(const Mat<Type::Dynamic, Type::Dynamic, T>& A);

	template <size_t N, typename T>
	bool IsPositiveDefinite(const Mat<N, N, T>& A);

	template <typename T>
	bool IsPositiveDefinite(const Mat<Type::Dynamic, Type::Dynamic, T>& A);

	template <size_t M, size_t N, typename T>
	bool IsTridiagonalMat(const Mat<M, N, T>& A);

	template <typename T>
	bool IsTridiagonalMat(const Mat<Type::Dynamic, Type::Dynamic, T>& A);

	template <size_t M, size_t N, typename T>
	bool IsSingularMat(const Mat<M, N, T>& A);

	template <typename T>
	bool IsSingularMat(const Mat<Type::Dynamic, Type::Dynamic, T>& A);

	template <size_t M, size_t N, size_t O, typename T>
	constexpr bool CanBeSolved(const Mat<M, N, T>& A, const Vec<O, T>& b);

	template <typename T>
	bool CanBeSolved(const Mat<Type::Dynamic, Type::Dynamic, T>& A, const Vec<Type::Dynamic, T>& b);
} // namespace MiniRenderer

// inline file
#include "Algorithm.inl"