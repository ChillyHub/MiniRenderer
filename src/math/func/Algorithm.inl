#pragma once

#include "Algorithm.h"

namespace MiniRenderer::Math
{
	// LU Decompose ////////////////////////////////////////////////////////////////
	// -----------------------------------------------------------------------------
	// Example ---------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	// Eliminate row: (this function used)
	//     _         _        _           _      _         _
	//     |  1 2 -1 |        |  1  0   0 |      | 1  2 -1 |
	// A = |  2 1 -2 |    L = |  2  1   0 |  U = | 0 -3  0 |
	//     | -3 1  1 |        | -3 -7/3 1 |      | 0  0 -2 |
	// 
	// Eliminate column:
	//     _         _        _          _       _        _
	//     |  1 2 -1 |        |  1  0  0 |       | 1 2 -1 |
	// A = |  2 1 -2 |    L = |  2 -3  0 |   U = | 0 1  0 |
	//     | -3 1  1 |        | -3  7 -2 |       | 0 0  1 |
	// --------------------------------------------------------
	// A = L * U;
	// -----------------------------------------------------------------------------
	template <size_t N, typename T>
	inline void LUDecompose(const Mat<N, N, T>& A, Mat<N, N, T>& L, Mat<N, N, T>& U)
	{
		Mat<N, N, T> AA(A);
		for (size_t k = 0; k < N; ++k)
		{
			if (AA[k][k] == T(0))
				throw std::runtime_error(S("ERROR: [") + __func__ + "] Matrix A can not LU decompose");

			L[k][k] = T(1);
			U[k][k] = AA[k][k];
			for (size_t i = k + 1; i < N; ++i)
			{
				L[k][i] = AA[k][i] / U[k][k];
				U[i][k] = AA[i][k];
			}
			for (size_t i = k + 1; i < N; ++i)
			{
				for (size_t j = k + 1; j < N; ++j)
				{
					AA[i][j] -= L[k][j] * U[i][k];
				}
			}
		}
	}

	template <typename T>
	inline void LUDecompose(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& L, Mat<Type::Dynamic, Type::Dynamic, T>& U)
	{
		const size_t N = A.col_len();
		
		if (!IsSquareMat(A))
			throw std::runtime_error(S("ERROR: [") + __func__ + "] Matrix A is not a square matrix");

		Mat<Type::Dynamic, Type::Dynamic, T> AA(A);
		L = std::move(Mat<Type::Dynamic, Type::Dynamic, T>(N, N));
		U = std::move(Mat<Type::Dynamic, Type::Dynamic, T>(N, N));
		for (size_t k = 0; k < N; ++k)
		{
			if (AA[k][k] == T(0))
				throw std::runtime_error(S("ERROR: [") + __func__ + "] Matrix A can not LU decompose");
			
			L[k][k] = T(1);
			U[k][k] = AA[k][k];
			for (size_t i = k + 1; i < N; ++i)
			{
				L[k][i] = AA[k][i] / U[k][k];
				U[i][k] = AA[i][k];
			}
			for (size_t i = k + 1; i < N; ++i)
			{
				for (size_t j = k + 1; j < N; ++j)
				{
					AA[i][j] -= L[k][j] * U[i][k];
				}
			}
		}
	}

	template <size_t N, typename T>
	inline void LUPDecompose(const Mat<N, N, T>& A, Mat<N, N, T>& L, Mat<N, N, T>& U, Mat<N, N, T>& P)
	{
		Mat<N, N, T> AA(A);
		Vec<N, size_t> order;
		for (size_t i = 0; i < N; ++i)
			order[i] = i;

		for (size_t k = 0; k < N; ++k)
		{
			T p = T(0);
			size_t kmax = k;
			for (size_t i = k; i < N; ++i)
			{
				if (std::abs(AA[k][i]) > p)
				{
					p = std::abs(AA[k][i]);
					kmax = i;
				}
			}

			if (p == T(0))
				throw std::runtime_error(S("ERROR: [") + __func__ + "] Matrix A is a singular matrix, can not decompose");

			if (k != kmax)
			{
				std::swap(order[k], order[kmax]);
				for (size_t i = 0; i < N; ++i)
				{
					std::swap(AA[i][k], AA[i][kmax]);
				}
			}

			for (size_t i = k + 1; i < N; ++i)
				AA[k][i] /= AA[k][k];
			for (size_t i = k + 1; i < N; ++i)
			{
				for (size_t j = k + 1; j < N; ++j)
					AA[i][j] -= AA[k][j] * AA[i][k];
			}
		}

		for (size_t i = 0; i < N; ++i)
		{
			for (size_t j = 0; j < N; ++j)
			{
				if (i < j)
					L[i][j] = AA[i][j];
				else if (i > j)
					U[i][j] = AA[i][j];
				else
				{
					L[i][j] = T(1);
					U[i][j] = AA[i][j];
				}
			}
			P[order[i]][i] = T(1);
		}
	}

	template <typename T>
	inline void LUPDecompose(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& L, 
		Mat<Type::Dynamic, Type::Dynamic, T>& U, 
		Mat<Type::Dynamic, Type::Dynamic, T>& P)
	{
		const size_t N = A.col_len();

		if (!IsSquareMat(A))
			throw std::runtime_error(S("ERROR: [") + __func__ + "] Matrix A is not a square matrix");
		
		Mat<Type::Dynamic, Type::Dynamic, T> AA(A);
		Vec<Type::Dynamic, size_t> order(N);
		for (size_t i = 0; i < N; ++i)
			order[i] = i;

		for (size_t k = 0; k < N; ++k)
		{
			T p = T(0);
			size_t kmax = k;
			for (size_t i = k; i < N; ++i)
			{
				if (std::abs(AA[k][i]) > p)
				{
					p = std::abs(AA[k][i]);
					kmax = i;
				}
			}

			if (p == T(0))
				throw std::runtime_error(S("ERROR: [") + __func__ + "] Matrix A is a singular matrix, can not decompose");

			if (k != kmax)
			{
				std::swap(order[k], order[kmax]);
				for (size_t i = 0; i < N; ++i)
				{
					std::swap(AA[i][k], AA[i][kmax]);
				}
			}
			
			for (size_t i = k + 1; i < N; ++i)
				AA[k][i] /= AA[k][k];
			for (size_t i = k + 1; i < N; ++i)
			{
				for (size_t j = k + 1; j < N; ++j)
					AA[i][j] -= AA[k][j] * AA[i][k];
			}
		}

		L = std::move(Mat<Type::Dynamic, Type::Dynamic, T>(N, N));
		U = std::move(Mat<Type::Dynamic, Type::Dynamic, T>(N, N));
		P = std::move(Mat<Type::Dynamic, Type::Dynamic, T>(N, N));
		for (size_t i = 0; i < N; ++i)
		{
			for (size_t j = 0; j < N; ++j)
			{
				if (i < j)
					L[i][j] = AA[i][j];
				else if (i > j)
					U[i][j] = AA[i][j];
				else
				{
					L[i][j] = T(1);
					U[i][j] = AA[i][j];
				}
			}
			P[order[i]][i] = T(1);
		}
	}

	template <size_t N, typename T>
	inline Vec<N, T> SolveLU(const Mat<N, N, T>& L, const Mat<N, N, T>& U, const Vec<N, T>& b)
	{
		Vec<N, T> c;
		c[0] = b[0];
		for (size_t k = 1; k < N; ++k)
		{
			c[k] = b[k];
			for (size_t i = 0; i < k; ++i)
				c[k] -= c[i] * L[i][k];
		}

		Vec<N, T> x;
		x[N - 1] = c[N - 1] / U[N - 1][N - 1];
		for (int k = N - 2; k >= 0; --k)
		{
			x[k] = c[k];
			for (size_t i = N - 1; i > k; --i)
				x[k] -= x[i] * U[i][k];
			x[k] /= U[k][k];
		}

		return x;
	}

	template <typename T>
	inline Vec<Type::Dynamic, T> SolveLU(const Mat<Type::Dynamic, Type::Dynamic, T>& L,
		const Mat<Type::Dynamic, Type::Dynamic, T>& U,
		const Vec<Type::Dynamic, T>& b)
	{
		const size_t N = L.col_len();

		if (!IsSquareMat(L) || !IsSquareMat(U))
			throw std::runtime_error(S("ERROR: [") + __func__ + "] Matrix L or U are not correct matrix");
		
		Vec<Type::Dynamic, T> c(N);
		c[0] = b[0];
		for (size_t k = 1; k < N; ++k)
		{
			c[k] = b[k];
			for (size_t i = 0; i < k; ++i)
				c[k] -= c[i] * L[i][k];
		}

		Vec<Type::Dynamic, T> x(N);
		x[N - 1] = c[N - 1] / U[N - 1][N - 1];
		for (int k = N - 2; k >= 0; --k)
		{
			x[k] = c[k];
			for (size_t i = N - 1; i > k; --i)
				x[k] -= x[i] * U[i][k];
			x[k] /= U[k][k];
		}

		return x;
	}

	// function
	template <size_t M, size_t N, typename T>
	inline T Cofactor(const Mat<M, N, T>& A, size_t m, size_t n)
	{
		if (m >= M || n >= N)
			throw std::runtime_error(S("ERROR: [") + __func__ + "] Index out of range");

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
				res[i][j] = A[a][b];
				++j;
			}
			++i;
		}
		return ((m + n) % 2 ? -1 : 1) * Det(res);
	}

	template <typename T>
	inline T Cofactor(const Mat<Type::Dynamic, Type::Dynamic, T>& A, size_t m, size_t n)
	{
		const size_t M = A.col_len(), N = A.row_len();
		if (m >= M || n >= N)
			throw std::runtime_error(S("ERROR: [") + __func__ + "] Index out of range");

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
				res[i][j] = A[a][b];
				++j;
			}
			++i;
		}
		return ((m + n) % 2 ? -1 : 1) * Det(res);
	}

	template <size_t M, size_t N, typename T>
	inline Mat<N, M, T> Adjugate(const Mat<M, N, T>& A)
	{
		Mat<M, N, T> tmp;
		for (size_t i = 0; i < N; ++i)
			for (size_t j = 0; j < M; ++j)
				tmp[i][j] = Cofactor(A, j, i);

		Mat<N, M, T> res;
		for (size_t i = 0; i < M; ++i)
			for (size_t j = 0; j < N; ++j)
				res[i][j] = tmp[j][i];
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> Adjugate(const Mat<Type::Dynamic, Type::Dynamic, T>& A)
	{
		const size_t M = A.col_len(), N = A.row_len();
		Mat<Type::Dynamic, Type::Dynamic, T> tmp(M, N);
		for (size_t i = 0; i < N; ++i)
			for (size_t j = 0; j < M; ++j)
				tmp[i][j] = Cofactor(A, j, i);

		Mat<Type::Dynamic, Type::Dynamic, T> res(N, M);
		for (size_t i = 0; i < M; ++i)
			for (size_t j = 0; j < N; ++j)
				res[i][j] = tmp[j][i];
		return res;
	}

	template <size_t N, typename T>
	Vec<N, T> PrincipalMinors(const Mat<N, N, T>& A)
	{
		// Bareiss Algorithm
		T pivot = T(1);
		Vec<N, T> res;
		Mat<N, N, T> AA(A);
		for (size_t k = 0; k < N - 1; ++k)
		{
			for (size_t i = k + 1; i < N; ++i)
			{
				for (size_t j = k + 1; j < N; ++j)
				{
					AA[i][j] = AA[k][k] * AA[i][j] - AA[i][k] * AA[k][j];
					AA[i][j] /= pivot;
				}
			}
			pivot = AA[k][k];
			res[k] = AA[k][k];
		}
		res[N - 1] = AA[N - 1][N - 1];
		return res;
	}

	template <typename T>
	Vec<Type::Dynamic, T> PrincipalMinors(const Mat<Type::Dynamic, Type::Dynamic, T>& A)
	{
		// Bareiss Algorithm
		const size_t N = A.col_len();
		if (!IsSquareMat(A))
			throw std::runtime_error(S("ERROR: [") + __func__ + "] Matrix A is not a square matrix");
		
		T pivot = T(1);
		Vec<Type::Dynamic, T> res(N);
		Mat<Type::Dynamic, Type::Dynamic, T> AA(A, N, N);
		for (size_t k = 0; k < N - 1; ++k)
		{
			for (size_t i = k + 1; i < N; ++i)
			{
				for (size_t j = k + 1; j < N; ++j)
				{
					AA[i][j] = AA[k][k] * AA[i][j] - AA[i][k] * AA[k][j];
					AA[i][j] /= pivot;
				}
			}
			pivot = AA[k][k];
			res[k] = AA[k][k];
		}
		res[N - 1] = AA[N - 1][N - 1];
		return res;
	}

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

	template <typename T>
	inline T Det(const Mat<3, 3, T>& a)
	{
		T sum = T();
		sum += a[0][0] * Cofactor(a, 0, 0);
		sum += a[0][1] * Cofactor(a, 1, 0);
		sum += a[0][2] * Cofactor(a, 2, 0);
		return sum;
	}

	template <typename T>
	inline T Det(const Mat<4, 4, T>& a)
	{
		T sum = T();
		for (size_t i = 0; i < 4; ++i)
			sum += a[0][i] * Cofactor(a, i, 0);
		return sum;
	}

	template <size_t N, typename T>
	inline T Det(const Mat<N, N, T>& a)
	{
		// Bareiss Algorithm
		T pivot = T(1);
		Mat<N, N, T> A(a);
		for (size_t k = 0; k < N - 1; ++k)
		{
			for (size_t i = k + 1; i < N; ++i)
			{
				for (size_t j = k + 1; j < N; ++j)
				{
					A[i][j] = A[k][k] * A[i][j] - A[i][k] * A[k][j];
					A[i][j] /= pivot;
				}
			}
			pivot = A[k][k];
		}
		return A[N - 1][N - 1];
	}

	template <typename T>
	inline T Det(const Mat<Type::Dynamic, Type::Dynamic, T>& a)
	{
		const size_t N = a.col_len();
		if (!IsSquareMat(a))
			throw std::runtime_error(S("ERROR: [") + __func__ + "] Matrix A is not a square matrix");

		T pivot = T(1);
		Mat<Type::Dynamic, Type::Dynamic, T> A(a, N, N);
		for (size_t k = 0; k < N - 1; ++k)
		{
			for (size_t i = k + 1; i < N; ++i)
			{
				for (size_t j = k + 1; j < N; ++j)
				{
					A[i][j] = A[k][k] * A[i][j] - A[i][k] * A[k][j];
					A[i][j] /= pivot;
				}
			}
			pivot = A[k][k];
		}
		return A[N - 1][N - 1];
	}

	// correct
	template <size_t M, size_t N, typename T>
	inline bool IsSquareMat(const Mat<M, N, T>& A)
	{
		if (M == N)
			return true;
		return false;
	}

	template <typename T>
	inline bool IsSquareMat(const Mat<Type::Dynamic, Type::Dynamic, T>& A)
	{
		if (A.col_len() == A.row_len())
			return true;
		return false;
	}

	template <size_t N, typename T>
	inline bool IsPositiveDefinite(const Mat<N, N, T>& A)
	{
		auto pm = PrincipalMinors(A);
		for (size_t i = 0; i < pm.length(); ++i)
		{
			if (pm[i] < 0)
				return false;
		}
		return true;
	}

	template <typename T>
	inline bool IsPositiveDefinite(const Mat<Type::Dynamic, Type::Dynamic, T>& A)
	{
		if (!IsSquareMat(A))
			return false;

		auto pm = PrincipalMinors(A);
		for (size_t i = 1; i <= pm.length(); ++i)
		{
			if (pm[i] < 0)
				return false;
		}
		return true;
	}
}