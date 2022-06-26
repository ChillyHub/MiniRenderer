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
				throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A can not LU decompose");

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
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A is not a square matrix");

		Mat<Type::Dynamic, Type::Dynamic, T> AA(A);
		L = std::move(Mat<Type::Dynamic, Type::Dynamic, T>(N, N));
		U = std::move(Mat<Type::Dynamic, Type::Dynamic, T>(N, N));
		for (size_t k = 0; k < N; ++k)
		{
			if (AA[k][k] == T(0))
				throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A can not LU decompose");
			
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
				throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A is a singular matrix, can not decompose");

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
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A is not a square matrix");
		
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
				throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A is a singular matrix, can not decompose");

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

	template <size_t M, size_t N, typename T>
	inline void QRDecompose(const Mat<M, N, T>& A, Mat<M, M, T>& Q, Mat<M, N, T>& R)
	{
		QRDecompose_HouseholderReflection(A, Q, R);
	}

	template <typename T>
	inline void QRDecompose(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R)
	{
		QRDecompose_HouseholderReflection(A, Q, R);
	}

	template <size_t M, size_t N, typename T>
	inline void QRDecompose_HouseholderReflection(const Mat<M, N, T>& A, Mat<M, M, T>& Q, Mat<M, N, T>& R)
	{
		Q = Mat<M, M, T>(T(1));
		R = Mat<M, N, T>(A);
		for (size_t i = 0; i < N; ++i)
		{
			Vec<M, T> w, x;
			for (size_t j = i; j < M; ++j)
				x[j] = R[i][j];
			w[i] = Norm(x);

			Vec<M, T> v = w - x;

			T vtv = Dot(v, v);
			Mat<M, M, T> H(T(1));
			if (vtv != T(0))
			{
				Mat<M, M, T> P = v * Transpose(v) / vtv;
				H -= P * T(2);
			}

			Q = Q * H;
			R = H * R;
		}
	}

	template <typename T>
	inline void QRDecompose_HouseholderReflection(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R)
	{
		const size_t M = A.col_len(), N = A.row_len();

		Q = Mat<Type::Dynamic, Type::Dynamic, T>(T(1), M, M);
		R = Mat<Type::Dynamic, Type::Dynamic, T>(A);
		for (size_t i = 0; i < N; ++i)
		{
			Vec<Type::Dynamic, T> w(M - i), x(M - i);
			for (size_t j = 0; j < M - i; ++j)
				x[j] = R[i][i + j];
			w[0] = Norm(x);

			Vec<Type::Dynamic, T> v = w - x;

			T vtv = Dot(v, v);
			Mat<Type::Dynamic, Type::Dynamic, T> H(T(1), M, M);
			if (vtv != T(0))
			{
				Mat<Type::Dynamic, Type::Dynamic, T> P = v * Transpose(v) / vtv;
				for (size_t j = i; j < M; ++j)
				{
					for (size_t k = i; k < M; ++k)
					{
						H[j][k] -= P[j - i][k - i] * T(2);
					}
				}
			}

			Q = Q * H;
			R = H * R;
		}
	}

	template <size_t M, size_t N, typename T>
	inline void QRDecompose_GivensRotation(const Mat<M, N, T>& A, Mat<M, M, T>& Q, Mat<M, N, T>& R)
	{
		Q = Mat<M, M, T>(T(1));
		R = Mat<M, N, T>(A);
		for (size_t i = 0; i < N; ++i)
		{
			for (size_t j = M - 1; j > i; --j)
			{
				T t, s, c;
				if (R[i][j] == T(0))
				{
					continue;
				}
				else if (R[i][j - 1] == T(0))
				{
					s = T(1);
					c = T(0);
				}
				else if (Abs(R[i][j - 1]) < Abs(R[i][j]))
				{
					t = R[i][j - 1] / R[i][j];
					s = T(1) / std::sqrt(T(1) + t * t);
					c = s * t;
				}
				else
				{
					t = R[i][j] / R[i][j - 1];
					c = T(1) / std::sqrt(T(1) + t * t);
					s = c * t;
				}

				Mat<M, M, T> GT(T(1));
				GT[j - 1][j - 1] = c;
				GT[j - 1][j] = s;
				GT[j][j - 1] = -s;
				GT[j][j] = c;
				Q = Q * GT;

				for (size_t k = 0; k < N; ++k)
				{
					T o = R[k][j - 1], p = R[k][j];
					R[k][j - 1] = c * o + s * p;
					R[k][j] = -s * o + c * p;
				}
			}
		}
	}

	template <typename T>
	inline void QRDecompose_GivensRotation(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R)
	{
		const size_t M = A.col_len(), N = A.row_len();
		
		Q = Mat<Type::Dynamic, Type::Dynamic, T>(T(1), M, M);
		R = Mat<Type::Dynamic, Type::Dynamic, T>(A);
		for (size_t i = 0; i < N; ++i)
		{
			for (size_t j = M - 1; j > i; --j)
			{
				T t, s, c;
				if (R[i][j] == T(0))
				{
					continue;
				}
				else if (R[i][j - 1] == T(0))
				{
					s = T(1);
					c = T(0);
				}
				else if (Abs(R[i][j - 1]) < Abs(R[i][j]))
				{
					t = R[i][j - 1] / R[i][j];
					s = T(1) / std::sqrt(T(1) + t * t);
					c = s * t;
				}
				else
				{
					t = R[i][j] / R[i][j - 1];
					c = T(1) / std::sqrt(T(1) + t * t);
					s = c * t;
				}

				Mat<Type::Dynamic, Type::Dynamic, T> GT(T(1), M, M);
				GT[j - 1][j - 1] = c;
				GT[j - 1][j] = s;
				GT[j][j - 1] = -s;
				GT[j][j] = c;
				Q = Q * GT;

				for (size_t k = 0; k < N; ++k)
				{
					T o = R[k][j - 1], p = R[k][j];
					R[k][j - 1] = c * o + s * p;
					R[k][j] = -s * o + c * p;
				}
			}
		}
	}

	template <size_t M, size_t N, typename T>
	inline void QRDecompose_ModifiedGramSchmidtOrthogonalization(const Mat<M, N, T>& A, Mat<M, M, T>& Q, Mat<M, N, T>& R)
	{
		for (size_t i = 0; i < N; ++i)
		{
			// Number of iterations M = 1
			Vec<M, T> y = A[i];
			for (size_t j = 0; j < i; ++j)
			{
				R[i][j] = Dot(Q[j], y);
				y -= R[i][j] * Q[j];
			}
			R[i][i] = Norm(y);
			Q[i] = y / R[i][i];
		}
	}

	template <typename T>
	inline void QRDecompose_ModifiedGramSchmidtOrthogonalization(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
		Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R)
	{
		const size_t M = A.col_len(), N = A.row_len();
		
		Q = Mat<Type::Dynamic, Type::Dynamic, T>(T(0), M, M);
		R = Mat<Type::Dynamic, Type::Dynamic, T>(T(0), M, N);
		for (size_t i = 0; i < N; ++i)
		{
			// Number of iterations M = 1
			Vec<Type::Dynamic, T> y = A[i];
			for (size_t j = 0; j < i; ++j)
			{
				R[i][j] = Dot(Q[j], y);
				y -= R[i][j] * Q[j];
			}
			R[i][i] = Norm(y);
			Q[i] = y / R[i][i];
		}
	}

	template <size_t N, typename T>
	inline Vec<N + 1, T> FindEigenByTridiagonalMat(const Mat<N, N, T>& A)
	{
		if (!IsTridiagonalMat(A))
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A is not a tridiagonal matrix");

		Vec<N, T> b;
		Vec<N - 1, T> a, c;
		for (size_t i = 0; i < N; ++i)
			b[i] = A[i][i];
		for (size_t i = 0; i < N - 1; ++i)
		{
			a[i] = A[i][i + 1];
			c[i] = A[i + 1][i];
		}

		Vec<N + 1, T> res, ores, oores;
		ores[0] = -b[0];
		ores[1] = T(1);
		oores[0] = T(1);
		for (size_t i = 1; i < N; ++i)
		{
			T ac = a[i - 1] * c[i - 1];
			res[0] = -b[i] * ores[0] - ac * oores[0];
			for (size_t j = 1; j <= i; ++j)
			{
				res[j] = -b[i] * ores[j] + ores[j - 1] - ac * oores[j];
			}

			for (size_t j = 0; j < i; ++j)
				oores[j] = ores[j];
			for (size_t j = 0; j <= i; ++j)
				ores[j] = res[j];
			oores[i] = T(1);
			ores[i + 1] = T(1);
		}
		res[N] = T(1);

		Vec<N + 1, T> v;
		for (size_t i = 0; i <= N; ++i)
			v[i] = res[N - i];
		return v;
	}

	template <typename T>
	inline Vec<Type::Dynamic, T> FindEigenByTridiagonalMat(const Mat<Type::Dynamic, Type::Dynamic, T>& A)
	{
		const size_t N = A.col_len();

		if (!IsTridiagonalMat(A))
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A is not a tridiagonal matrix");

		Vec<Type::Dynamic, T> b(N);
		Vec<Type::Dynamic, T> a(N - 1), c(N - 1);
		for (size_t i = 0; i < N; ++i)
			b[i] = A[i][i];
		for (size_t i = 0; i < N - 1; ++i)
		{
			a[i] = A[i][i + 1];
			c[i] = A[i + 1][i];
		}

		Vec<Type::Dynamic, T> res(N + 1);
		Vec<Type::Dynamic, T> ores(N + 1);
		Vec<Type::Dynamic, T> oores(N + 1);
		ores[0] = -b[0];
		ores[1] = T(1);
		oores[0] = T(1);
		for (size_t i = 1; i < N; ++i)
		{
			T ac = a[i - 1] * c[i - 1];
			res[0] = -b[i] * ores[0] - ac * oores[0];
			for (size_t j = 1; j <= i; ++j)
			{
				res[j] = -b[i] * ores[j] + ores[j - 1] - ac * oores[j];
			}

			for (size_t j = 0; j < i; ++j)
				oores[j] = ores[j];
			for (size_t j = 0; j <= i; ++j)
				ores[j] = res[j];
			oores[i] = T(1);
			ores[i + 1] = T(1);
		}
		res[N] = T(1);

		Vec<Type::Dynamic, T> v(N + 1);
		for (size_t i = 0; i <= N; ++i)
			v[i] = res[N - i];
		return v;
	}

	template <size_t N, typename T>
	inline Vec<N, T> Solve(const Mat<N, N, T>& A, const Vec<N, T>& b)
	{
		Mat<N, N, T> L, U, P;
		LUPDecompose(A, L, U, P);
		return SolveLUP(L, U, P, b);
	}

	template <typename T>
	inline Vec<Type::Dynamic, T> Solve(const Mat<Type::Dynamic, Type::Dynamic, T>& A, const Vec<Type::Dynamic, T>& b)
	{
		const size_t N = A.col_len();
		
		Mat<Type::Dynamic, Type::Dynamic, T> L(N, N), U(N, N), P(N, N);
		LUPDecompose(A, L, U, P);
		return SolveLUP(L, U, P, b);
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
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix L or U are not square matrix");
		
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

	template <size_t N, typename T>
	inline Vec<N, T> SolveLUP(const Mat<N, N, T>& L, const Mat<N, N, T>& U, const Mat<N, N, T>& P, const Vec<N, T>& b)
	{
		return SolveLU(L, U, P * b);
	}

	template <typename T>
	inline Vec<Type::Dynamic, T> SolveLUP(const Mat<Type::Dynamic, Type::Dynamic, T>& L,
		const Mat<Type::Dynamic, Type::Dynamic, T>& U,
		const Mat<Type::Dynamic, Type::Dynamic, T>& P,
		const Vec<Type::Dynamic, T>& b)
	{
		if (!IsSquareMat(P))
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix P are not square matrix");

		return SolveLU(L, U, P * b);
	}

	template <size_t N, typename T>
	inline Vec<N, T> SolveQR(const Mat<N, N, T>& Q, const Mat<N, N, T>& R, const Vec<N, T>& b)
	{
		Vec<N, T> c;
		Mat<N, N, T> L, U, P;
		LUPDecompose(Q, L, U, P);
		c = SolveLUP(L, U, P, b);

		Vec<N, T> x;
		x[N - 1] = c[N - 1] / R[N - 1][N - 1];
		for (int k = N - 2; k >= 0; --k)
		{
			x[k] = c[k];
			for (size_t i = N - 1; i > k; --i)
				x[k] -= x[i] * R[i][k];
			x[k] /= R[k][k];
		}

		return x;
	}

	template <typename T>
	inline Vec<Type::Dynamic, T> SolveQR(const Mat<Type::Dynamic, Type::Dynamic, T>& Q,
		const Mat<Type::Dynamic, Type::Dynamic, T>& R, const Vec<Type::Dynamic, T>& b)
	{
		const size_t N = Q.col_len();

		if (!IsSquareMat(Q) || !IsSquareMat(R))
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix Q or R are not square matrix");

		if (Q.col_len() != R.col_len() || Q.col_len() != b.length())
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrixs and vector size not match");

		Vec<Type::Dynamic, T> c(N);
		Mat<Type::Dynamic, Type::Dynamic, T> L(N, N);
		Mat<Type::Dynamic, Type::Dynamic, T> U(N, N);
		Mat<Type::Dynamic, Type::Dynamic, T> P(N, N);
		LUPDecompose(Q, L, U, P);
		c = SolveLUP(L, U, P, b);

		Vec<Type::Dynamic, T> x(N);
		x[N - 1] = c[N - 1] / R[N - 1][N - 1];
		for (int k = N - 2; k >= 0; --k)
		{
			x[k] = c[k];
			for (size_t i = N - 1; i > k; --i)
				x[k] -= x[i] * R[i][k];
			x[k] /= R[k][k];
		}

		return x;
	}

	// function
	template <size_t M, size_t N, typename T>
	inline T Cofactor(const Mat<M, N, T>& A, size_t m, size_t n)
	{
		if (m >= M || n >= N)
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");

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
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Index out of range");

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
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A is not a square matrix");
		
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
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A is not a square matrix");

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

	template <typename T>
	inline Mat<1, 1, T> Inverse(const Mat<1, 1, T>& a)
	{
		return Mat<1, 1, T>{ T(1) / a[0][0] };
	}

	template <typename T>
	inline Mat<2, 2, T> Inverse(const Mat<2, 2, T>& a)
	{
		return Adjugate(a) / Det(a);
	}

	template <typename T>
	inline Mat<3, 3, T> Inverse(const Mat<3, 3, T>& a)
	{
		return Adjugate(a) / Det(a);
	}

	template <typename T>
	inline Mat<4, 4, T> Inverse(const Mat<4, 4, T>& a)
	{
		return Adjugate(a) / Det(a);
	}

	template <size_t N, typename T>
	inline Mat<N, N, T> Inverse(const Mat<N, N, T>& a)
	{
		Mat<N, N, T> L, U;
		LUDecompose(a, L, U);
		
		Mat<N, N, T> IL, IU;
		for (size_t i = 0; i < N; ++i)
		{
			IL[i][i] = T(1);
			for (size_t j = i + 1; j < N; ++j)
			{
				for (size_t k = i; k < j; ++k)
				{
					IL[i][j] -= L[k][j] * IL[i][k];
				}
			}
		}
		for (int i = N - 1; i >= 0; --i)
		{
			IU[i][i] = T(1) / U[i][i];
			for (int j = i - 1; j >= 0; --j)
			{
				for (size_t k = i; k > j; --k)
				{
					IU[i][j] -= U[k][j] * IU[i][k];
				}
				IU[i][j] /= U[j][j];
			}
		}

		return IU * IL;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> Inverse(const Mat<Type::Dynamic, Type::Dynamic, T>& a)
	{
		const size_t N = a.col_len();

		if (!IsSquareMat(a))
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A is not a square matrix");

		Mat<Type::Dynamic, Type::Dynamic, T> L, U;
		LUDecompose(a, L, U);

		Mat<Type::Dynamic, Type::Dynamic, T> IL(N, N), IU(N, N);
		for (size_t i = 0; i < N; ++i)
		{
			IL[i][i] = T(1);
			for (size_t j = i + 1; j < N; ++j)
			{
				for (size_t k = i; k < j; ++k)
				{
					IL[i][j] -= L[k][j] * IL[i][k];
				}
			}
		}
		for (int i = N - 1; i >= 0; --i)
		{
			IU[i][i] = T(1) / U[i][i];
			for (int j = i - 1; j >= 0; --j)
			{
				for (size_t k = i; k > j; --k)
				{
					IU[i][j] -= U[k][j] * IU[i][k];
				}
				IU[i][j] /= U[j][j];
			}
		}

		return IU * IL;
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

	template <size_t M, size_t N, typename T>
	inline bool IsRegularMat(const Mat<M, N, T>& A)
	{
		size_t len = A[0].length();
		for (size_t i = 1; i < N; ++i)
			if (A[i].length() != len)
				return false;
		return true;
	}

	template <typename T>
	inline bool IsRegularMat(const Mat<Type::Dynamic, Type::Dynamic, T>& A)
	{
		if (A.row_len() == 0)
			return false;
		
		size_t len = A[0].length();
		for (size_t i = 1; i < A.row_len(); ++i)
			if (A[i].length() != len)
				return false;
		return true;
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

	template <size_t M, size_t N, typename T>
	inline bool IsTridiagonalMat(const Mat<M, N, T>& A)
	{
		if (!IsSquareMat(A))
			return false;

		for (size_t i = 0; i < M - 2; ++i)
			for (size_t j = i + 2; j < M; ++j)
				if (A[i][j] > Epsilon || A[i][j] < -Epsilon)
					return false;

		for (size_t i = 2; i < M; ++i)
			for (size_t j = 0; j < i - 1; ++j)
				if (A[i][j] > Epsilon || A[i][j] < -Epsilon)
					return false;

		return true;
	}

	template <typename T>
	inline bool IsTridiagonalMat(const Mat<Type::Dynamic, Type::Dynamic, T>& A)
	{
		const size_t M = A.col_len();
		
		if (!IsSquareMat(A))
			return false;

		for (size_t i = 0; i < M - 2; ++i)
			for (size_t j = i + 2; j < M; ++j)
				if (A[i][j] > Epsilon || A[i][j] < -Epsilon)
					return false;

		for (size_t i = 2; i < M; ++i)
			for (size_t j = 0; j < i - 1; ++j)
				if (A[i][j] > Epsilon || A[i][j] < -Epsilon)
					return false;

		return true;
	}

	template <size_t M, size_t N, typename T>
	inline bool IsSingularMat(const Mat<M, N, T>& A)
	{
		if (!IsSquareMat(A))
			return false;

		if (Abs(Det(A)) < Epsilon)
			return true;
		return false;
	}

	template <typename T>
	inline bool IsSingularMat(const Mat<Type::Dynamic, Type::Dynamic, T>& A)
	{
		if (!IsSquareMat(A))
			return false;

		if (Abs(Det(A)) < Epsilon)
			return true;
		return false;
	}

	template <size_t M, size_t N, size_t O, typename T>
	inline constexpr bool CanBeSolved(const Mat<M, N, T>& A, const Vec<O, T>& b)
	{
		return N == O;
	}

	template <typename T>
	inline bool CanBeSolved(const Mat<Type::Dynamic, Type::Dynamic, T>& A, const Vec<Type::Dynamic, T>& b)
	{
		return A.row_len() == b.length();
	}
} // namespace MiniRenderer