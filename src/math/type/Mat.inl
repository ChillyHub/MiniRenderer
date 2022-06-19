#pragma once

#include "Mat.h"

namespace MiniRenderer
{
	/////////////////////////////////////////////////////
	// Matrix: Mat<N, T>, Mat2, Mat3, Mat4
	//---------------------------------------------------

	// Mat ----------------------------------------------
	// --------------------------------------------------
	template <size_t M, size_t N, typename T>
	inline constexpr Mat<M, N, T>::Mat()
	{
		for (size_t i = 0; i < N; ++i)
			m[i] = Vec<M, T>();
	}

	template <size_t M, size_t N, typename T>
	inline constexpr Mat<M, N, T>::Mat(const T* p)
	{
		auto ptr = p;
		for (size_t i = 0; i < N; ++i)
		{
			Vec<M, T> vec;
			for (size_t j = 0; j < M; ++j)
				vec[j] = *ptr++;
			m[i] = std::move(vec);
		}
	}

	template <size_t M, size_t N, typename T>
	inline constexpr Mat<M, N, T>::Mat(const MT& src)
	{
		for (size_t i = 0; i < N; ++i)
			m[i] = src[i];
	}

	template <size_t M, size_t N, typename T>
	template <typename U>
	inline constexpr Mat<M, N, T>::Mat(const U& v)
	{
		auto len = M < N ? M : N;
		for (size_t i = 0; i < N; ++i)
			m[i] = Vec<M, T>();
		for (size_t i = 0; i < len; ++i)
			m[i][i] = static_cast<T>(v);
	}

	template <size_t M, size_t N, typename T>
	template <typename U>
	inline constexpr Mat<M, N, T>::Mat(const std::initializer_list<U>& l)
	{
		auto it = l.begin();
		for (size_t i = 0; i < N; ++i)
			m[i] = Vec<M, T>();
		for (size_t i = 0; i < M; ++i)
			for (size_t j = 0; j < N; ++j)
				m[i][j] = static_cast<T>(*it++);
	}

	template <size_t M, size_t N, typename T>
	template <typename U>
	inline constexpr Mat<M, N, T>::Mat(const std::initializer_list<Vec<M, U>>& l)
	{
		auto it = l.begin();
		for (size_t i = 0; i < N; ++i)
			m[i] = *it++;
	}

	template <size_t M, size_t N, typename T>
	template <size_t O, size_t P, typename U>
	inline constexpr Mat<M, N, T>::Mat(const Mat<O, P, U>& src)
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (i < P)
				m[i] = src[i];
			else
				m[i] = Vec<M, T>();
		}
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T>::Col& Mat<M, N, T>::operator[] (size_t i)
	{
		assert(i >= 0 && i < N);
		return m[i];
	}

	template <size_t M, size_t N, typename T>
	inline constexpr const Mat<M, N, T>::Col& Mat<M, N, T>::operator[] (size_t i) const
	{
		assert(i >= 0 && i < N);
		return m[i];
	}

	template <size_t M, size_t N, typename T>
	inline T* Mat<M, N, T>::data()
	{
		return &m[0][0];
	}

	template <size_t M, size_t N, typename T>
	inline constexpr size_t Mat<M, N, T>::length() const
	{
		return M * N;
	}

	template <size_t M, size_t N, typename T>
	Mat<M, N, T>::Col Mat<M, N, T>::GetCol(size_t i) const
	{
		assert(i >= 0 && i < N);
		return m[i];
	}

	template <size_t M, size_t N, typename T>
	Mat<M, N, T>::Row Mat<M, N, T>::GetRow(size_t i) const
	{
		assert(i >= 0 && i < M);
		Row res;
		for (size_t j = 0; j < N; ++j)
			res[j] = m[j][i];
		return res;
	}

	template <size_t M, size_t N, typename T>
	template <typename U>
	void Mat<M, N, T>::SetCol(size_t i, const Vec<M, U>& col)
	{
		m[i] = col;
	}

	template <size_t M, size_t N, typename T>
	template <typename U>
	void Mat<M, N, T>::SetRow(size_t i, const Vec<N, U>& row)
	{
		for (size_t j = 0; j < N; ++j)
			m[j][i] = row[j];
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T>& Mat<M, N, T>::operator++()
	{
		for (size_t i = 0; i < N; ++i)
			++m[i];
		return *this;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T>& Mat<M, N, T>::operator--()
	{
		for (size_t i = 0; i < N; ++i)
			--m[i];
		return *this;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> Mat<M, N, T>::operator++(int)
	{
		Mat<M, N, T> res(*this);
		++* this;
		return res;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> Mat<M, N, T>::operator--(int)
	{
		Mat<M, N, T> res(*this);
		--* this;
		return res;
	}

	template <size_t M, size_t N, typename T>
	template <typename U>
	inline Mat<M, N, T>& Mat<M, N, T>::operator= (const Mat<M, N, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
			m[i] = rhs[i];
		return *this;
	}
	
	template <size_t M, size_t N, typename T>
	template <typename U>
	inline Mat<M, N, T>& Mat<M, N, T>::operator+= (U rhs)
	{
		for (size_t i = 0; i < N; ++i)
			m[i] += rhs;
		return *this;
	}
	
	template <size_t M, size_t N, typename T>
	template <typename U>
	inline Mat<M, N, T>& Mat<M, N, T>::operator+= (const Mat<M, N, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
			m[i] += rhs[i];
		return *this;
	}

	template <size_t M, size_t N, typename T>
	template <typename U>
	inline Mat<M, N, T>& Mat<M, N, T>::operator-= (U rhs)
	{
		for (size_t i = 0; i < N; ++i)
			m[i] -= rhs;
		return *this;
	}

	template <size_t M, size_t N, typename T>
	template <typename U>
	inline Mat<M, N, T>& Mat<M, N, T>::operator-= (const Mat<M, N, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
			m[i] -= rhs[i];
		return *this;
	}

	template <size_t M, size_t N, typename T>
	template <typename U>
	inline Mat<M, N, T>& Mat<M, N, T>::operator*= (U rhs)
	{
		for (size_t i = 0; i < N; ++i)
			m[i] *= rhs;
		return *this;
	}

	template <size_t M, size_t N, typename T>
	template <typename U>
	inline Mat<M, N, T>& Mat<M, N, T>::operator*= (const Mat<M, N, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
			m[i] *= rhs[i];
		return *this;
	}

	template <size_t M, size_t N, typename T>
	template <typename U>
	inline Mat<M, N, T>& Mat<M, N, T>::operator/= (U rhs)
	{
		for (size_t i = 0; i < N; ++i)
			m[i] /= rhs;
		return *this;
	}

	template <size_t M, size_t N, typename T>
	template <typename U>
	inline Mat<M, N, T>& Mat<M, N, T>::operator/= (const Mat<M, N, U>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
			m[i] /= rhs[i];
		return *this;
	}

	// Mat2 ---------------------------------------------
	// --------------------------------------------------
	template <typename T>
	inline constexpr Mat<2, 2, T>::Mat()
	{
		m[0] = Col();
		m[1] = Col();
	}

	template <typename T>
	inline constexpr Mat<2, 2, T>::Mat(const T* p)
	{
		auto ptr = p;
		m[0] = Col();
		m[1] = Col();
		m[0][0] = *p++;
		m[1][0] = *p++;
		m[0][1] = *p++;
		m[1][1] = *p++;
	}

	template <typename T>
	inline constexpr Mat<2, 2, T>::Mat(const MT& src)
	{
		m[0] = src[0];
		m[1] = src[1];
	}

	template <typename T>
	template <typename U>
	inline constexpr Mat<2, 2, T>::Mat(const U& v)
	{
		m[0] = Col();
		m[1] = Col();
		m[0][0] = static_cast<T>(v);
		m[1][1] = static_cast<T>(v);
	}

	template <typename T>
	template <typename U1, typename U2>
	constexpr Mat<2, 2, T>::Mat(const Vec<2, U1>& c1, const Vec<2, U2>& c2)
	{
		m[0] = c1;
		m[1] = c2;
	}

	template <typename T>
	template <size_t O, size_t P, typename U>
	inline constexpr Mat<2, 2, T>::Mat(const Mat<O, P, U>& src)
	{
		m[0] = Vec<2, T>(src[0]);
		if (P > 1)
			m[1] = Vec<2, T>(src[1]);
	}

	template <typename T>
	template <typename A, typename B,
		      typename C, typename D>
	constexpr Mat<2, 2, T>::Mat(A a, B b, C c, D d)
	{
		m[0] = Col();
		m[1] = Col();
		m[0][0] = a;
		m[1][0] = b;
		m[0][1] = c;
		m[1][1] = d;
	}

	template <typename T>
	inline Mat<2, 2, T>::Col& Mat<2, 2, T>::operator[] (size_t i)
	{
		assert(i >= 0 && i < 2);
		return m[i];
	}

	template <typename T>
	inline constexpr const Mat<2, 2, T>::Col& Mat<2, 2, T>::operator[] (size_t i) const
	{
		assert(i >= 0 && i < 2);
		return m[i];
	}

	template <typename T>
	inline T* Mat<2, 2, T>::data()
	{
		return &m[0][0];
	}

	template <typename T>
	inline constexpr size_t Mat<2, 2, T>::length() const
	{
		return 4;
	}

	template <typename T>
	Mat<2, 2, T>::Col Mat<2, 2, T>::GetCol(size_t i) const
	{
		assert(i >= 0 && i < 2);
		return m[i];
	}

	template <typename T>
	Mat<2, 2, T>::Row Mat<2, 2, T>::GetRow(size_t i) const
	{
		assert(i >= 0 && i < 2);
		Row res;
		res[0] = m[0][i];
		res[1] = m[1][i];
		return res;
	}

	template <typename T>
	template <typename U>
	void Mat<2, 2, T>::SetCol(size_t i, const Vec<2, U>& col)
	{
		assert(i >= 0 && i < 2);
		m[i] = col;
	}

	template <typename T>
	template <typename U>
	void Mat<2, 2, T>::SetRow(size_t i, const Vec<2, U>& row)
	{
		assert(i >= 0 && i < 2);
		m[0][i] = row[0];
		m[1][i] = row[1];
	}

	template <typename T>
	inline Mat<2, 2, T>& Mat<2, 2, T>::operator++()
	{
		++m[0];
		++m[1];
		return *this;
	}

	template <typename T>
	inline Mat<2, 2, T>& Mat<2, 2, T>::operator--()
	{
		--m[0];
		--m[1];
		return *this;
	}

	template <typename T>
	inline Mat<2, 2, T> Mat<2, 2, T>::operator++(int)
	{
		Mat<2, 2, T> res(*this);
		++* this;
		return res;
	}

	template <typename T>
	inline Mat<2, 2, T> Mat<2, 2, T>::operator--(int)
	{
		Mat<2, 2, T> res(*this);
		--* this;
		return res;
	}

	template <typename T>
	template <typename U>
	inline Mat<2, 2, T>& Mat<2, 2, T>::operator= (const Mat<2, 2, U>& rhs)
	{
		m[0] = rhs[0];
		m[1] = rhs[1];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<2, 2, T>& Mat<2, 2, T>::operator+= (U rhs)
	{
		m[0] += rhs;
		m[1] += rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<2, 2, T>& Mat<2, 2, T>::operator+= (const Mat<2, 2, U>& rhs)
	{
		m[0] += rhs[0];
		m[1] += rhs[1];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<2, 2, T>& Mat<2, 2, T>::operator-= (U rhs)
	{
		m[0] -= rhs;
		m[1] -= rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<2, 2, T>& Mat<2, 2, T>::operator-= (const Mat<2, 2, U>& rhs)
	{
		m[0] -= rhs[0];
		m[1] -= rhs[1];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<2, 2, T>& Mat<2, 2, T>::operator*= (U rhs)
	{
		m[0] *= rhs;
		m[1] *= rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<2, 2, T>& Mat<2, 2, T>::operator*= (const Mat<2, 2, U>& rhs)
	{
		m[0] *= rhs[0];
		m[1] *= rhs[1];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<2, 2, T>& Mat<2, 2, T>::operator/= (U rhs)
	{
		m[0] /= rhs;
		m[1] /= rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<2, 2, T>& Mat<2, 2, T>::operator/= (const Mat<2, 2, U>& rhs)
	{
		m[0] /= rhs[0];
		m[1] /= rhs[1];
		return *this;
	}

	// Mat3 ---------------------------------------------
	// --------------------------------------------------
	template <typename T>
	inline constexpr Mat<3, 3, T>::Mat()
	{
		m[0] = Col();
		m[1] = Col();
		m[2] = Col();
	}

	template <typename T>
	inline constexpr Mat<3, 3, T>::Mat(const T* p)
	{
		auto ptr = p;
		m[0] = Col();
		m[1] = Col();
		m[2] = Col();
		m[0][0] = *p++;
		m[1][0] = *p++;
		m[2][0] = *p++;
		m[0][1] = *p++;
		m[1][1] = *p++;
		m[2][1] = *p++;
		m[0][1] = *p++;
		m[1][1] = *p++;
		m[2][1] = *p++;
	}

	template <typename T>
	inline constexpr Mat<3, 3, T>::Mat(const MT& src)
	{
		m[0] = src[0];
		m[1] = src[1];
		m[2] = src[2];
	}

	template <typename T>
	template <typename U>
	inline constexpr Mat<3, 3, T>::Mat(const U& v)
	{
		m[0] = Col();
		m[1] = Col();
		m[2] = Col();
		m[0][0] = static_cast<T>(v);
		m[1][1] = static_cast<T>(v);
		m[2][2] = static_cast<T>(v);
	}

	template <typename T>
	template <typename U1, typename U2, typename U3>
	constexpr Mat<3, 3, T>::Mat(const Vec<3, U1>& c1, 
								const Vec<3, U2>& c2, 
								const Vec<3, U3>& c3)
	{
		m[0] = c1;
		m[1] = c2;
		m[2] = c3;
	}

	template <typename T>
	template <size_t O, size_t P, typename U>
	inline constexpr Mat<3, 3, T>::Mat(const Mat<O, P, U>& src)
	{
		m[0] = Vec<3, T>(src[0]);
		if (P > 1)
			m[1] = Vec<3, T>(src[1]);
		if (P > 2)
			m[2] = Vec<3, T>(src[2]);
	}

	template <typename T>
	template <typename A, typename B, typename C,
		      typename D, typename E, typename F,
		      typename G, typename H, typename I>
	constexpr Mat<3, 3, T>::Mat(A a, B b, C c,
								D d, E e, F f,
								G g, H h, I i)
	{
		m[0] = Col();
		m[1] = Col();
		m[2] = Col();
		m[0][0] = static_cast<T>(a);
		m[1][0] = static_cast<T>(b);
		m[2][0] = static_cast<T>(c);
		m[0][1] = static_cast<T>(d);
		m[1][1] = static_cast<T>(e);
		m[2][1] = static_cast<T>(f);
		m[0][2] = static_cast<T>(g);
		m[1][2] = static_cast<T>(h);
		m[2][2] = static_cast<T>(i);
	}

	template <typename T>
	inline Mat<3, 3, T>::Col& Mat<3, 3, T>::operator[] (size_t i)
	{
		assert(i >= 0 && i < 3);
		return m[i];
	}

	template <typename T>
	inline constexpr const Mat<3, 3, T>::Col& Mat<3, 3, T>::operator[] (size_t i) const
	{
		assert(i >= 0 && i < 3);
		return m[i];
	}

	template <typename T>
	inline T* Mat<3, 3, T>::data()
	{
		return &m[0][0];
	}

	template <typename T>
	inline constexpr size_t Mat<3, 3, T>::length() const
	{
		return 9;
	}

	template <typename T>
	Mat<3, 3, T>::Col Mat<3, 3, T>::GetCol(size_t i) const
	{
		assert(i >= 0 && i < 3);
		return m[i];
	}

	template <typename T>
	Mat<3, 3, T>::Row Mat<3, 3, T>::GetRow(size_t i) const
	{
		assert(i >= 0 && i < 3);
		Row res;
		res[0] = m[0][i];
		res[1] = m[1][i];
		res[2] = m[2][i];
		return res;
	}

	template <typename T>
	template <typename U>
	void Mat<3, 3, T>::SetCol(size_t i, const Vec<3, U>& col)
	{
		assert(i >= 0 && i < 3);
		m[i] = col;
	}

	template <typename T>
	template <typename U>
	void Mat<3, 3, T>::SetRow(size_t i, const Vec<3, U>& row)
	{
		assert(i >= 0 && i < 3);
		m[0][i] = row[0];
		m[1][i] = row[1];
		m[2][i] = row[2];
	}

	template <typename T>
	inline Mat<3, 3, T>& Mat<3, 3, T>::operator++()
	{
		++m[0];
		++m[1];
		++m[2];
		return *this;
	}

	template <typename T>
	inline Mat<3, 3, T>& Mat<3, 3, T>::operator--()
	{
		--m[0];
		--m[1];
		--m[2];
		return *this;
	}

	template <typename T>
	inline Mat<3, 3, T> Mat<3, 3, T>::operator++(int)
	{
		Mat<3, 3, T> res(*this);
		++* this;
		return res;
	}

	template <typename T>
	inline Mat<3, 3, T> Mat<3, 3, T>::operator--(int)
	{
		Mat<3, 3, T> res(*this);
		--* this;
		return res;
	}

	template <typename T>
	template <typename U>
	inline Mat<3, 3, T>& Mat<3, 3, T>::operator= (const Mat<3, 3, U>& rhs)
	{
		m[0] = rhs[0];
		m[1] = rhs[1];
		m[2] = rhs[2];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<3, 3, T>& Mat<3, 3, T>::operator+= (U rhs)
	{
		m[0] += rhs;
		m[1] += rhs;
		m[2] += rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<3, 3, T>& Mat<3, 3, T>::operator+= (const Mat<3, 3, U>& rhs)
	{
		m[0] += rhs[0];
		m[1] += rhs[1];
		m[2] += rhs[2];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<3, 3, T>& Mat<3, 3, T>::operator-= (U rhs)
	{
		m[0] -= rhs;
		m[1] -= rhs;
		m[2] -= rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<3, 3, T>& Mat<3, 3, T>::operator-= (const Mat<3, 3, U>& rhs)
	{
		m[0] -= rhs[0];
		m[1] -= rhs[1];
		m[2] -= rhs[2];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<3, 3, T>& Mat<3, 3, T>::operator*= (U rhs)
	{
		m[0] *= rhs;
		m[1] *= rhs;
		m[2] *= rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<3, 3, T>& Mat<3, 3, T>::operator*= (const Mat<3, 3, U>& rhs)
	{
		m[0] *= rhs[0];
		m[1] *= rhs[1];
		m[2] *= rhs[2];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<3, 3, T>& Mat<3, 3, T>::operator/= (U rhs)
	{
		m[0] /= rhs;
		m[1] /= rhs;
		m[2] /= rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<3, 3, T>& Mat<3, 3, T>::operator/= (const Mat<3, 3, U>& rhs)
	{
		m[0] /= rhs[0];
		m[1] /= rhs[1];
		m[2] /= rhs[2];
		return *this;
	}

	// Mat4 ---------------------------------------------
	// --------------------------------------------------
	template <typename T>
	inline constexpr Mat<4, 4, T>::Mat()
	{
		m[0] = Col();
		m[1] = Col();
		m[2] = Col();
		m[3] = Col();
	}

	template <typename T>
	inline constexpr Mat<4, 4, T>::Mat(const T* p)
	{
		auto ptr = p;
		m[0] = Col();
		m[1] = Col();
		m[2] = Col();
		m[3] = Col();
		m[0][0] = *p++;
		m[1][0] = *p++;
		m[2][0] = *p++;
		m[3][0] = *p++;
		m[0][1] = *p++;
		m[1][1] = *p++;
		m[2][1] = *p++;
		m[3][1] = *p++;
		m[0][2] = *p++;
		m[1][2] = *p++;
		m[2][2] = *p++;
		m[3][2] = *p++;
		m[0][3] = *p++;
		m[1][3] = *p++;
		m[2][3] = *p++;
		m[3][3] = *p++;
	}

	template <typename T>
	inline constexpr Mat<4, 4, T>::Mat(const MT& src)
	{
		m[0] = src[0];
		m[1] = src[1];
		m[2] = src[2];
		m[3] = src[3];
	}

	template <typename T>
	template <typename U>
	inline constexpr Mat<4, 4, T>::Mat(const U& v)
	{
		m[0] = Col();
		m[1] = Col();
		m[2] = Col();
		m[3] = Col();
		m[0][0] = static_cast<T>(v);
		m[1][1] = static_cast<T>(v);
		m[2][2] = static_cast<T>(v);
		m[3][3] = static_cast<T>(v);
	}

	template <typename T>
	template <typename U1, typename U2,
			  typename U3, typename U4>
	constexpr Mat<4, 4, T>::Mat(const Vec<4, U1>& c1,
								const Vec<4, U2>& c2,
								const Vec<4, U3>& c3,
								const Vec<4, U4>& c4)
	{
		m[0] = c1;
		m[1] = c2;
		m[2] = c3;
		m[3] = c4;
	}

	template <typename T>
	template <size_t O, size_t P, typename U>
	inline constexpr Mat<4, 4, T>::Mat(const Mat<O, P, U>& src)
	{
		m[0] = Vec<4, T>(src[0]);
		if (P > 1)
			m[1] = Vec<4, T>(src[1]);
		if (P > 2)
			m[2] = Vec<4, T>(src[2]);
		if (P > 3)
			m[3] = Vec<4, T>(src[3]);
	}

	template <typename T>
	template <typename A, typename B, typename C, typename D,
			  typename E, typename F, typename G, typename H,
			  typename I, typename J, typename K, typename L,
			  typename M, typename N, typename O, typename P>
	constexpr Mat<4, 4, T>::Mat(A a, B b, C c, D d,
								E e, F f, G g, H h,
								I i, J j, K k, L l,
								M w, N n, O o, P p)
	{
		m[0] = Col();
		m[1] = Col();
		m[2] = Col();
		m[3] = Col();
		m[0][0] = static_cast<T>(a);
		m[1][0] = static_cast<T>(b);
		m[2][0] = static_cast<T>(c);
		m[3][0] = static_cast<T>(d);
		m[0][1] = static_cast<T>(e);
		m[1][1] = static_cast<T>(f);
		m[2][1] = static_cast<T>(g);
		m[3][1] = static_cast<T>(h);
		m[0][2] = static_cast<T>(i);
		m[1][2] = static_cast<T>(j);
		m[2][2] = static_cast<T>(k);
		m[3][2] = static_cast<T>(l);
		m[0][3] = static_cast<T>(w);
		m[1][3] = static_cast<T>(n);
		m[2][3] = static_cast<T>(o);
		m[3][3] = static_cast<T>(p);
	}

	template <typename T>
	inline Mat<4, 4, T>::Col& Mat<4, 4, T>::operator[] (size_t i)
	{
		assert(i >= 0 && i < 4);
		return m[i];
	}

	template <typename T>
	inline constexpr const Mat<4, 4, T>::Col& Mat<4, 4, T>::operator[] (size_t i) const
	{
		assert(i >= 0 && i < 4);
		return m[i];
	}

	template <typename T>
	inline T* Mat<4, 4, T>::data()
	{
		return &m[0][0];
	}

	template <typename T>
	inline constexpr size_t Mat<4, 4, T>::length() const
	{
		return 16;
	}

	template <typename T>
	Mat<4, 4, T>::Col Mat<4, 4, T>::GetCol(size_t i) const
	{
		assert(i >= 0 && i < 4);
		return m[i];
	}

	template <typename T>
	Mat<4, 4, T>::Row Mat<4, 4, T>::GetRow(size_t i) const
	{
		assert(i >= 0 && i < 4);
		Row res;
		res[0] = m[0][i];
		res[1] = m[1][i];
		res[2] = m[2][i];
		res[3] = m[3][i];
		return res;
	}

	template <typename T>
	template <typename U>
	void Mat<4, 4, T>::SetCol(size_t i, const Vec<3, U>& col)
	{
		assert(i >= 0 && i < 4);
		m[i] = col;
	}

	template <typename T>
	template <typename U>
	void Mat<4, 4, T>::SetRow(size_t i, const Vec<3, U>& row)
	{
		assert(i >= 0 && i < 4);
		m[0][i] = row[0];
		m[1][i] = row[1];
		m[2][i] = row[2];
		m[3][i] = row[3];
	}

	template <typename T>
	inline Mat<4, 4, T>& Mat<4, 4, T>::operator++()
	{
		++m[0];
		++m[1];
		++m[2];
		++m[3];
		return *this;
	}

	template <typename T>
	inline Mat<4, 4, T>& Mat<4, 4, T>::operator--()
	{
		--m[0];
		--m[1];
		--m[2];
		--m[3];
		return *this;
	}

	template <typename T>
	inline Mat<4, 4, T> Mat<4, 4, T>::operator++(int)
	{
		Mat<4, 4, T> res(*this);
		++* this;
		return res;
	}

	template <typename T>
	inline Mat<4, 4, T> Mat<4, 4, T>::operator--(int)
	{
		Mat<4, 4, T> res(*this);
		--* this;
		return res;
	}

	template <typename T>
	template <typename U>
	inline Mat<4, 4, T>& Mat<4, 4, T>::operator= (const Mat<4, 4, U>& rhs)
	{
		m[0] = rhs[0];
		m[1] = rhs[1];
		m[2] = rhs[2];
		m[3] = rhs[3];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<4, 4, T>& Mat<4, 4, T>::operator+= (U rhs)
	{
		m[0] += rhs;
		m[1] += rhs;
		m[2] += rhs;
		m[3] += rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<4, 4, T>& Mat<4, 4, T>::operator+= (const Mat<4, 4, U>& rhs)
	{
		m[0] += rhs[0];
		m[1] += rhs[1];
		m[2] += rhs[2];
		m[3] += rhs[3];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<4, 4, T>& Mat<4, 4, T>::operator-= (U rhs)
	{
		m[0] -= rhs;
		m[1] -= rhs;
		m[2] -= rhs;
		m[3] -= rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<4, 4, T>& Mat<4, 4, T>::operator-= (const Mat<4, 4, U>& rhs)
	{
		m[0] -= rhs[0];
		m[1] -= rhs[1];
		m[2] -= rhs[2];
		m[3] -= rhs[3];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<4, 4, T>& Mat<4, 4, T>::operator*= (U rhs)
	{
		m[0] *= rhs;
		m[1] *= rhs;
		m[2] *= rhs;
		m[3] *= rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<4, 4, T>& Mat<4, 4, T>::operator*= (const Mat<4, 4, U>& rhs)
	{
		m[0] *= rhs[0];
		m[1] *= rhs[1];
		m[2] *= rhs[2];
		m[3] *= rhs[3];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<4, 4, T>& Mat<4, 4, T>::operator/= (U rhs)
	{
		m[0] /= rhs;
		m[1] /= rhs;
		m[2] /= rhs;
		m[3] /= rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<4, 4, T>& Mat<4, 4, T>::operator/= (const Mat<4, 4, U>& rhs)
	{
		m[0] /= rhs[0];
		m[1] /= rhs[1];
		m[2] /= rhs[2];
		m[3] /= rhs[3];
		return *this;
	}

	// Mat Dynamic --------------------------------------
	// --------------------------------------------------
	template <typename T>
	inline constexpr Mat<Type::Dynamic, Type::Dynamic, T>::Mat()
		: collen(0), rowlen(0)
	{
		m = nullptr;
	}

	template <typename T>
	inline constexpr Mat<Type::Dynamic, Type::Dynamic, T>::Mat(size_t col_len, size_t row_len)
		: collen(col_len), rowlen(row_len)
	{
		m = new Vec<Type::Dynamic, T>[rowlen];
		for (size_t i = 0; i < rowlen; ++i)
			m[i] = Vec<Type::Dynamic, T>(collen);
	}

	template <typename T>
	inline constexpr Mat<Type::Dynamic, Type::Dynamic, T>::Mat(const T* p, size_t col_len, size_t row_len)
		: collen(col_len), rowlen(row_len)
	{
		auto ptr = p;
		m = new Vec<Type::Dynamic, T>[rowlen];
		for (size_t i = 0; i < rowlen; ++i)
		{
			Vec<Type::Dynamic, T> vec(collen);
			for (size_t j = 0; j < collen; ++j)
				vec[j] = *ptr++;
			m[i] = std::move(vec);
		}
	}

	template <typename T>
	inline constexpr Mat<Type::Dynamic, Type::Dynamic, T>::Mat(const MT& src)
		: collen(src.col_len()), rowlen(src.row_len())
	{
		m = new Vec<Type::Dynamic, T>[rowlen];
		for (size_t i = 0; i < rowlen; ++i)
			m[i] = src[i];
	}

	template <typename T>
	template <typename U>
	inline constexpr Mat<Type::Dynamic, Type::Dynamic, T>::Mat(const U& v, size_t col_len, size_t row_len)
		: collen(col_len), rowlen(row_len)
	{
		auto len = collen < rowlen ? collen : rowlen;
		m = new Vec<Type::Dynamic, T>[rowlen];
		for (size_t i = 0; i < rowlen; ++i)
			m[i] = Vec<Type::Dynamic, T>(collen);
		for (size_t i = 0; i < len; ++i)
			m[i][i] = static_cast<T>(v);
	}

	template <typename T>
	template <typename U>
	inline constexpr Mat<Type::Dynamic, Type::Dynamic, T>::Mat(const std::initializer_list<U>& l, size_t col_len, size_t row_len)
		: collen(col_len), rowlen(row_len)
	{
		auto it = l.begin();
		m = new Vec<Type::Dynamic, T>[rowlen];
		for (size_t i = 0; i < rowlen; ++i)
			m[i] = Vec<Type::Dynamic, T>(collen);
		for (size_t i = 0; i < collen; ++i)
			for (size_t j = 0; j < rowlen; ++j)
				m[i][j] = static_cast<T>(*it++);
	}

	template <typename T>
	template <size_t M, typename U>
	inline constexpr Mat<Type::Dynamic, Type::Dynamic, T>::Mat(const std::initializer_list<Vec<M, U>>& l)
		: collen(M), rowlen(l.end() - l.begin())
	{
		auto it = l.begin();
		m = new Vec<Type::Dynamic, T>[rowlen];
		for (size_t i = 0; i < rowlen; ++i)
			m[i] = *it++;
	}

	template <typename T>
	template <typename U>
	inline constexpr Mat<Type::Dynamic, Type::Dynamic, T>::Mat(const std::initializer_list<Vec<Type::Dynamic, U>>& l)
		: collen(l.begin()->length()), rowlen(l.end() - l.begin())
	{
		auto it = l.begin();
		m = new Vec<Type::Dynamic, T>[rowlen];
		for (size_t i = 0; i < rowlen; ++i)
			m[i] = *it++;
	}

	template <typename T>
	template <size_t O, size_t P, typename U>
	inline constexpr Mat<Type::Dynamic, Type::Dynamic, T>::Mat(const Mat<O, P, U>& src)
		: collen(O), rowlen(P)
	{
		m = new Vec<Type::Dynamic, T>[rowlen];
		for (size_t i = 0; i < rowlen; ++i)
		{
			m[i] = src[i];
		}
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T>::Col& 
		Mat<Type::Dynamic, Type::Dynamic, T>::operator[] (size_t i)
	{
		assert(i >= 0 && i < rowlen);
		return m[i];
	}

	template <typename T>
	inline constexpr const Mat<Type::Dynamic, Type::Dynamic, T>::Col& 
		Mat<Type::Dynamic, Type::Dynamic, T>::operator[] (size_t i) const
	{
		assert(i >= 0 && i < rowlen);
		return m[i];
	}

	template <typename T>
	inline T* Mat<Type::Dynamic, Type::Dynamic, T>::data()
	{
		return m;
	}

	template <typename T>
	inline size_t Mat<Type::Dynamic, Type::Dynamic, T>::length() const
	{
		return collen * rowlen;
	}

	template <typename T>
	inline size_t Mat<Type::Dynamic, Type::Dynamic, T>::col_len() const
	{
		return collen;
	}

	template <typename T>
	inline size_t Mat<Type::Dynamic, Type::Dynamic, T>::row_len() const
	{
		return rowlen;
	}

	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T>::Col 
		Mat<Type::Dynamic, Type::Dynamic, T>::GetCol(size_t i) const
	{
		assert(i >= 0 && i < rowlen);
		return m[i];
	}

	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T>::Row 
		Mat<Type::Dynamic, Type::Dynamic, T>::GetRow(size_t i) const
	{
		assert(i >= 0 && i < collen);
		Row res(rowlen);
		for (size_t j = 0; j < rowlen; ++j)
			res[j] = m[j][i];
		return res;
	}

	template <typename T>
	template <typename U>
	void Mat<Type::Dynamic, Type::Dynamic, T>::SetCol(size_t i, const Vec<Type::Dynamic, U>& col)
	{
		m[i] = col;
	}

	template <typename T>
	template <typename U>
	void Mat<Type::Dynamic, Type::Dynamic, T>::SetRow(size_t i, const Vec<Type::Dynamic, U>& row)
	{
		for (size_t j = 0; j < rowlen; ++j)
			m[j][i] = row[j];
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T>& Mat<Type::Dynamic, Type::Dynamic, T>::operator++()
	{
		for (size_t i = 0; i < rowlen; ++i)
			++m[i];
		return *this;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T>& Mat<Type::Dynamic, Type::Dynamic, T>::operator--()
	{
		for (size_t i = 0; i < rowlen; ++i)
			--m[i];
		return *this;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> Mat<Type::Dynamic, Type::Dynamic, T>::operator++(int)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(*this);
		++* this;
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> Mat<Type::Dynamic, Type::Dynamic, T>::operator--(int)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(*this);
		--* this;
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T>&
		Mat<Type::Dynamic, Type::Dynamic, T>::operator= (const Mat<Type::Dynamic, Type::Dynamic, T>& rhs)
	{
		if (rowlen != rhs.row_len())
		{
			delete[] m;
			rowlen = rhs.row_len();
			collen = rhs.col_len();
			m = new Vec<Type::Dynamic, T>[rowlen];
		}
		for (size_t i = 0; i < rowlen; ++i)
			m[i] = rhs[i];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<Type::Dynamic, Type::Dynamic, T>& 
		Mat<Type::Dynamic, Type::Dynamic, T>::operator= (const Mat<Type::Dynamic, Type::Dynamic, U>& rhs)
	{
		if (rowlen != rhs.row_len())
		{
			delete[] m;
			rowlen = rhs.row_len();
			collen = rhs.col_len();
			m = new Vec<Type::Dynamic, U>[rowlen];
		}
		for (size_t i = 0; i < rowlen; ++i)
			m[i] = rhs[i];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<Type::Dynamic, Type::Dynamic, T>& Mat<Type::Dynamic, Type::Dynamic, T>::operator+= (U rhs)
	{
		for (size_t i = 0; i < rowlen; ++i)
			m[i] += rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<Type::Dynamic, Type::Dynamic, T>& 
		Mat<Type::Dynamic, Type::Dynamic, T>::operator+= (const Mat<Type::Dynamic, Type::Dynamic, U>& rhs)
	{
		for (size_t i = 0; i < rowlen; ++i)
			if (i < rhs.row_len())
				m[i] += rhs[i];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<Type::Dynamic, Type::Dynamic, T>& Mat<Type::Dynamic, Type::Dynamic, T>::operator-= (U rhs)
	{
		for (size_t i = 0; i < rowlen; ++i)
			m[i] -= rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<Type::Dynamic, Type::Dynamic, T>& 
		Mat<Type::Dynamic, Type::Dynamic, T>::operator-= (const Mat<Type::Dynamic, Type::Dynamic, U>& rhs)
	{
		for (size_t i = 0; i < rowlen; ++i)
			if (i < rhs.row_len())
				m[i] -= rhs[i];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<Type::Dynamic, Type::Dynamic, T>& Mat<Type::Dynamic, Type::Dynamic, T>::operator*= (U rhs)
	{
		for (size_t i = 0; i < rowlen; ++i)
			m[i] *= rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<Type::Dynamic, Type::Dynamic, T>& 
		Mat<Type::Dynamic, Type::Dynamic, T>::operator*= (const Mat<Type::Dynamic, Type::Dynamic, U>& rhs)
	{
		for (size_t i = 0; i < rowlen; ++i)
			if (i < rhs.row_len())
				m[i] *= rhs[i];
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<Type::Dynamic, Type::Dynamic, T>& Mat<Type::Dynamic, Type::Dynamic, T>::operator/= (U rhs)
	{
		for (size_t i = 0; i < rowlen; ++i)
			m[i] /= rhs;
		return *this;
	}

	template <typename T>
	template <typename U>
	inline Mat<Type::Dynamic, Type::Dynamic, T>& 
		Mat<Type::Dynamic, Type::Dynamic, T>::operator/= (const Mat<Type::Dynamic, Type::Dynamic, U>& rhs)
	{
		for (size_t i = 0; i < rowlen; ++i)
			if (i < rhs.row_len())
				m[i] /= rhs[i];
		return *this;
	}

	// Mat operator STATIC ------------------------------
	// --------------------------------------------------
	template <size_t M, size_t N, typename T>
	inline constexpr Mat<M, N, T> operator+(const Mat<M, N, T>& r)
	{
		return r;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> operator-(const Mat<M, N, T>& r)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = -r[i];
		return res;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> operator+(const Mat<M, N, T>& l, const Mat<M, N, T>& r)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = l[i] + r[i];
		return res;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> operator-(const Mat<M, N, T>& l, const Mat<M, N, T>& r)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = l[i] - r[i];
		return res;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> operator+(const Mat<M, N, T>& l, T r)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = l[i] + r;
		return res;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> operator-(const Mat<M, N, T>& l, T r)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = l[i] - r;
		return res;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> operator+(T l, const Mat<M, N, T>& r)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = l + r[i];
		return res;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> operator-(T l, const Mat<M, N, T>& r)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = l - r[i];
		return res;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> operator*(const Mat<M, N, T>& l, T r)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = l[i] * r;
		return res;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> operator*(T l, const Mat<M, N, T>& r)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = l * r[i];
		return res;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> operator/(const Mat<M, N, T>& l, T r)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = l[i] / r;
		return res;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> operator/(T l, const Mat<M, N, T>& r)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = l / r[i];
		return res;
	}

	template <size_t M, size_t N, typename T>
	inline Mat<M, N, T> operator/(const Mat<M, N, T>& l, const Mat<M, N, T>& r)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			res[i] = l[i] / r[i];
		return res;
	}
 
	template <size_t M, size_t N, typename T>
	inline Vec<N, T> operator*(const Mat<M, N, T>& l, const Vec<N, T>& r)
	{
		Vec<N, T> res;
		for (size_t i = 0; i < N; ++i)
			res += l[i] * r[i];
		return res;
	}

	template <size_t M, size_t K, size_t N, typename T>
	inline Mat<M, N, T> operator*(const Mat<M, K, T>& l, const Mat<K, N, T>& r)
	{
		Mat<M, N, T> res;
		for (size_t i = 0; i < N; ++i)
			for (size_t k = 0; k < K; ++k)
				res[i] += l[k] * r[i][k];
		return res;
	}

	template <size_t M, size_t N, typename T>
	inline constexpr bool operator==(const Mat<M, N, T>& lhs, const Mat<M, N, T>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template <size_t M, size_t N, typename T>
	inline constexpr bool operator!=(const Mat<M, N, T>& lhs, const Mat<M, N, T>& rhs)
	{
		return !(lhs == rhs);
	}

	template <size_t M, size_t N, typename T>
	inline std::ostream& operator<<(std::ostream& os, const Mat<M, N, T>& rhs)
	{
		for (size_t i = 0; i < M; ++i)
		{
			auto row = rhs.GetRow(i);
			if (i == 0)
				os << "\n" << "[ ";
			else
				os << "  ";
			for (size_t j = 0; j < N; ++j)
			{
				os << row[j];
				if (j < N - 1)
					os << ", ";
			}
			if (i == M - 1)
				os << " ]";
			else
				os << " ;\n";
		}
		os << std::endl;
		return os;
	}

	// Mat operator DYNAMIC -----------------------------
	// --------------------------------------------------
	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> operator-(const Mat<Type::Dynamic, Type::Dynamic, T>& r)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(r);
		for (size_t i = 0; i < res.row_len(); ++i)
			res[i] = -res[i];
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> operator+(const Mat<Type::Dynamic, Type::Dynamic, T>& l, const Mat<Type::Dynamic, Type::Dynamic, T>& r)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(l);
		res += r;
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> operator-(const Mat<Type::Dynamic, Type::Dynamic, T>& l, const Mat<Type::Dynamic, Type::Dynamic, T>& r)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(l);
		res -= r;
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> operator+(const Mat<Type::Dynamic, Type::Dynamic, T>& l, T r)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(l);
		res += r;
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> operator-(const Mat<Type::Dynamic, Type::Dynamic, T>& l, T r)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(l);
		res -= r;
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> operator+(T l, const Mat<Type::Dynamic, Type::Dynamic, T>& r)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(r);
		res += l;
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> operator-(T l, const Mat<Type::Dynamic, Type::Dynamic, T>& r)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(r);
		res = -res;
		res += l;
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> operator*(const Mat<Type::Dynamic, Type::Dynamic, T>& l, T r)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(l);
		res *= r;
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> operator*(T l, const Mat<Type::Dynamic, Type::Dynamic, T>& r)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(r);
		res *= l;
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> operator/(const Mat<Type::Dynamic, Type::Dynamic, T>& l, T r)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(l);
		res /= r;
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> operator/(T l, const Mat<Type::Dynamic, Type::Dynamic, T>& r)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(r);
		for (size_t i = 0; i < res.col_len(); ++i)
			res[i] = l / r[i];
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> 
		operator/(const Mat<Type::Dynamic, Type::Dynamic, T>& l, const Mat<Type::Dynamic, Type::Dynamic, T>& r)
	{
		Mat<Type::Dynamic, Type::Dynamic, T> res(l);
		res /= r;
		return res;
	}

	template <typename T>
	inline Vec<Type::Dynamic, T> operator*(const Mat<Type::Dynamic, Type::Dynamic, T>& l, const Vec<Type::Dynamic, T>& r)
	{
		assert(l.row_len() == r.length());
		Vec<Type::Dynamic, T> res(l.col_len());
		for (size_t i = 0; i < r.length(); ++i)
			res += l[i] * r[i];
		return res;
	}

	template <typename T>
	inline Mat<Type::Dynamic, Type::Dynamic, T> operator*(const Mat<Type::Dynamic, Type::Dynamic, T>& l, const Mat<Type::Dynamic, Type::Dynamic, T>& r)
	{
		int m = l.col_len(), k1 = l.row_len(), k2 = r.col_len(), n = r.row_len();
		assert(k1 == k2);
		Mat<Type::Dynamic, Type::Dynamic, T> res(m, n);
		for (size_t i = 0; i < n; ++i)
			for (size_t k = 0; k < k1; ++k)
				res[i] += l[k] * r[i][k];
		return res;
	}

	template <typename T>
	inline constexpr bool operator==(const Mat<Type::Dynamic, Type::Dynamic, T>& lhs, const Mat<Type::Dynamic, Type::Dynamic, T>& rhs)
	{
		if (lhs.col_len() != rhs.col_len() || lhs.row_len() != rhs.row_len())
			return false;
		for (size_t i = 0; i < lhs.row_len(); ++i)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template <typename T>
	inline std::ostream& operator<<(std::ostream& os, const Mat<Type::Dynamic, Type::Dynamic, T>& rhs)
	{
		for (size_t i = 0; i < rhs.col_len(); ++i)
		{
			auto row = rhs.GetRow(i);
			if (i == 0)
				os << "\n" << "[ ";
			else
				os << "  ";
			for (size_t j = 0; j < rhs.row_len(); ++j)
			{
				os << row[j];
				if (j < rhs.row_len() - 1)
					os << ", ";
			}
			if (i == rhs.col_len() - 1)
				os << " ]";
			else
				os << " ;\n";
		}
		os << std::endl;
		return os;
	}
} // namespace MiniRenderer