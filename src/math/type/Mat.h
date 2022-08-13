#pragma once

#include "Base.h"
#include "Vec.h"

namespace MiniRenderer
{
	/////////////////////////////////////////////////////
	// Matrix: Mat<N, T>, Mat2, Mat3, Mat4
	//---------------------------------------------------
	
	template <size_t M, size_t N, typename T>
	struct Mat
	{
		typedef Vec<N, T> Row;
		typedef Vec<M, T> Col;
		typedef Mat<M, N, T> MT;
		typedef Mat<N, M, T> TT;

	private:
		Col m[N];

	public:
		constexpr Mat();
		constexpr explicit Mat(const T* p);
		constexpr Mat(const MT& src);

		template <typename U>
		constexpr Mat(const U& v);
		template <typename U>
		constexpr Mat(const std::initializer_list<U>& l);
		template <typename U>
		constexpr Mat(const std::initializer_list<Vec<M, U>>& l);
		template <size_t O, size_t P, typename U>
		constexpr explicit Mat(const Mat<O, P, U>& src);

		Col& operator[] (size_t i);
		constexpr const Col& operator[] (size_t i) const;

		T* data();
		constexpr size_t length() const;

		Col GetCol(size_t i) const;
		Row GetRow(size_t i) const;

		template <typename U>
		void SetCol(size_t i, const Vec<M, U>& col);
		template <typename U>
		void SetRow(size_t i, const Vec<N, U>& row);

		Mat<M, N, T>& operator++();
		Mat<M, N, T>& operator--();
		Mat<M, N, T> operator++(int);
		Mat<M, N, T> operator--(int);

		template <typename U>
		Mat<M, N, T>& operator= (const Mat<M, N, U>& rhs);
		template <typename U>
		Mat<M, N, T>& operator+= (U rhs);
		template <typename U>
		Mat<M, N, T>& operator+= (const Mat<M, N, U>& rhs);
		template <typename U>
		Mat<M, N, T>& operator-= (U rhs);
		template <typename U>
		Mat<M, N, T>& operator-= (const Mat<M, N, U>& rhs);
		template <typename U>
		Mat<M, N, T>& operator*= (U rhs);
		template <typename U>
		Mat<M, N, T>& operator*= (const Mat<M, N, U>& rhs);
		template <typename U>
		Mat<M, N, T>& operator/= (U rhs);
		template <typename U>
		Mat<M, N, T>& operator/= (const Mat<M, N, U>& rhs);
	};

	template <typename T>
	struct Mat<2, 2, T>
	{
		typedef Vec<2, T> Row;
		typedef Vec<2, T> Col;
		typedef Mat<2, 2, T> MT;
		typedef Mat<2, 2, T> TT;

	private:
		Col m[2];

	public:
		constexpr Mat();
		constexpr explicit Mat(const T* p);
		constexpr Mat(const MT& src);

		template <typename U>
		constexpr Mat(const U& v);
		template <typename U1, typename U2>
		constexpr Mat(const Vec<2, U1>& c1, const Vec<2, U2>& c2);
		template <size_t O, size_t P, typename U>
		constexpr explicit Mat(const Mat<O, P, U>& src);
		template <typename A, typename B,
				  typename C, typename D>
		constexpr Mat(A a, B b, C c, D d);

		Col& operator[] (size_t i);
		constexpr const Col& operator[] (size_t i) const;

		T* data();
		constexpr size_t length() const;

		Col GetCol(size_t i) const;
		Row GetRow(size_t i) const;

		template <typename U>
		void SetCol(size_t i, const Vec<2, U>& col);
		template <typename U>
		void SetRow(size_t i, const Vec<2, U>& row);

		Mat<2, 2, T>& operator++();
		Mat<2, 2, T>& operator--();
		Mat<2, 2, T> operator++(int);
		Mat<2, 2, T> operator--(int);

		template <typename U>
		Mat<2, 2, T>& operator= (const Mat<2, 2, U>& rhs);
		template <typename U>
		Mat<2, 2, T>& operator+= (U rhs);
		template <typename U>
		Mat<2, 2, T>& operator+= (const Mat<2, 2, U>& rhs);
		template <typename U>
		Mat<2, 2, T>& operator-= (U rhs);
		template <typename U>
		Mat<2, 2, T>& operator-= (const Mat<2, 2, U>& rhs);
		template <typename U>
		Mat<2, 2, T>& operator*= (U rhs);
		template <typename U>
		Mat<2, 2, T>& operator*= (const Mat<2, 2, U>& rhs);
		template <typename U>
		Mat<2, 2, T>& operator/= (U rhs);
		template <typename U>
		Mat<2, 2, T>& operator/= (const Mat<2, 2, U>& rhs);
	};

	template <typename T>
	struct Mat<3, 3, T>
	{
		typedef Vec<3, T> Row;
		typedef Vec<3, T> Col;
		typedef Mat<3, 3, T> MT;
		typedef Mat<3, 3, T> TT;

	private:
		Col m[3];

	public:
		constexpr Mat();
		constexpr explicit Mat(const T* p);
		constexpr Mat(const MT& src);

		template <typename U>
		constexpr Mat(const U& v);
		template <typename U1, typename U2, typename U3>
		constexpr Mat(const Vec<3, U1>& c1, 
			          const Vec<3, U2>& c2, 
			          const Vec<3, U3>& c3);
		template <size_t O, size_t P, typename U>
		constexpr explicit Mat(const Mat<O, P, U>& src);
		template <typename A, typename B, typename C,
			      typename D, typename E, typename F,
		          typename G, typename H, typename I>
		constexpr Mat(A a, B b, C c, 
					  D d, E e, F f,
					  G g, H h, I i);

		Col& operator[] (size_t i);
		constexpr const Col& operator[] (size_t i) const;

		T* data();
		constexpr size_t length() const;

		Col GetCol(size_t i) const;
		Row GetRow(size_t i) const;

		template <typename U>
		void SetCol(size_t i, const Vec<3, U>& col);
		template <typename U>
		void SetRow(size_t i, const Vec<3, U>& row);

		Mat<3, 3, T>& operator++();
		Mat<3, 3, T>& operator--();
		Mat<3, 3, T> operator++(int);
		Mat<3, 3, T> operator--(int);

		template <typename U>
		Mat<3, 3, T>& operator= (const Mat<3, 3, U>& rhs);
		template <typename U>
		Mat<3, 3, T>& operator+= (U rhs);
		template <typename U>
		Mat<3, 3, T>& operator+= (const Mat<3, 3, U>& rhs);
		template <typename U>
		Mat<3, 3, T>& operator-= (U rhs);
		template <typename U>
		Mat<3, 3, T>& operator-= (const Mat<3, 3, U>& rhs);
		template <typename U>
		Mat<3, 3, T>& operator*= (U rhs);
		template <typename U>
		Mat<3, 3, T>& operator*= (const Mat<3, 3, U>& rhs);
		template <typename U>
		Mat<3, 3, T>& operator/= (U rhs);
		template <typename U>
		Mat<3, 3, T>& operator/= (const Mat<3, 3, U>& rhs);
	};

	template <typename T>
	struct Mat<4, 4, T>
	{
		typedef Vec<4, T> Row;
		typedef Vec<4, T> Col;
		typedef Mat<4, 4, T> MT;
		typedef Mat<4, 4, T> TT;

	private:
		Col m[4];

	public:
		constexpr Mat();
		constexpr explicit Mat(const T* p);
		constexpr Mat(const MT& src);

		template <typename U>
		constexpr Mat(const U& v);
		template <typename U1, typename U2, 
				  typename U3, typename U4>
		constexpr Mat(const Vec<4, U1>& c1,
					  const Vec<4, U2>& c2,
					  const Vec<4, U3>& c3,
					  const Vec<4, U4>& c4);
		template <size_t O, size_t P, typename U>
		constexpr explicit Mat(const Mat<O, P, U>& src);
		template <typename A, typename B, typename C, typename D,
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M, typename N, typename O, typename P>
		constexpr Mat(A a, B b, C c, D d,
					  E e, F f, G g, H h,
					  I i, J j, K k, L l,
					  M m, N n, O o, P p);

		Col& operator[] (size_t i);
		constexpr const Col& operator[] (size_t i) const;

		T* data();
		constexpr size_t length() const;

		Col GetCol(size_t i) const;
		Row GetRow(size_t i) const;

		template <typename U>
		void SetCol(size_t i, const Vec<3, U>& col);
		template <typename U>
		void SetRow(size_t i, const Vec<3, U>& row);
		template <typename U>
		void SetCol(size_t i, const Vec<4, U>& col);
		template <typename U>
		void SetRow(size_t i, const Vec<4, U>& row);

		Mat<4, 4, T>& operator++();
		Mat<4, 4, T>& operator--();
		Mat<4, 4, T> operator++(int);
		Mat<4, 4, T> operator--(int);

		template <typename U>
		Mat<4, 4, T>& operator= (const Mat<4, 4, U>& rhs);
		template <typename U>
		Mat<4, 4, T>& operator+= (U rhs);
		template <typename U>
		Mat<4, 4, T>& operator+= (const Mat<4, 4, U>& rhs);
		template <typename U>
		Mat<4, 4, T>& operator-= (U rhs);
		template <typename U>
		Mat<4, 4, T>& operator-= (const Mat<4, 4, U>& rhs);
		template <typename U>
		Mat<4, 4, T>& operator*= (U rhs);
		template <typename U>
		Mat<4, 4, T>& operator*= (const Mat<4, 4, U>& rhs);
		template <typename U>
		Mat<4, 4, T>& operator/= (U rhs);
		template <typename U>
		Mat<4, 4, T>& operator/= (const Mat<4, 4, U>& rhs);
	};

	template <typename T>
	struct Mat<Type::Dynamic, Type::Dynamic, T>
	{
		typedef Vec<Type::Dynamic, T> Row;
		typedef Vec<Type::Dynamic, T> Col;
		typedef Mat<Type::Dynamic, Type::Dynamic, T> MT;
		typedef Mat<Type::Dynamic, Type::Dynamic, T> TT;

	private:
		Col* m;
		size_t collen;
		size_t rowlen;

	public:
		~Mat() { if (m) delete[] m; }

	public:
		constexpr Mat();
		constexpr Mat(size_t col_len, size_t row_len);
		constexpr explicit Mat(const T* p, size_t col_len, size_t row_len);
		constexpr Mat(const MT& src);

		template <typename U>
		constexpr Mat(const U& v, size_t col_len, size_t row_len);
		template <typename U>
		constexpr Mat(const std::initializer_list<U>& l, size_t col_len, size_t row_len);
		template <size_t M, typename U>
		constexpr Mat(const std::initializer_list<Vec<M, U>>& l);
		template <typename U>
		constexpr Mat(const std::initializer_list<Vec<Type::Dynamic, U>>& l);
		template <size_t O, size_t P, typename U>
		constexpr explicit Mat(const Mat<O, P, U>& src);

		Col& operator[] (size_t i);
		constexpr const Col& operator[] (size_t i) const;

		T* data();
		size_t length() const;
		size_t col_len() const;
		size_t row_len() const;

		Col GetCol(size_t i) const;
		Row GetRow(size_t i) const;

		template <typename U>
		void SetCol(size_t i, const Vec<Type::Dynamic, U>& col);
		template <typename U>
		void SetRow(size_t i, const Vec<Type::Dynamic, U>& row);

		Mat<Type::Dynamic, Type::Dynamic, T>& operator++();
		Mat<Type::Dynamic, Type::Dynamic, T>& operator--();
		Mat<Type::Dynamic, Type::Dynamic, T> operator++(int);
		Mat<Type::Dynamic, Type::Dynamic, T> operator--(int);

		Mat<Type::Dynamic, Type::Dynamic, T>& operator= (const Mat<Type::Dynamic, Type::Dynamic, T>& rhs);
		template <typename U>
		Mat<Type::Dynamic, Type::Dynamic, T>& operator= (const Mat<Type::Dynamic, Type::Dynamic, U>& rhs);
		template <typename U>
		Mat<Type::Dynamic, Type::Dynamic, T>& operator+= (U rhs);
		template <typename U>
		Mat<Type::Dynamic, Type::Dynamic, T>& operator+= (const Mat<Type::Dynamic, Type::Dynamic, U>& rhs);
		template <typename U>
		Mat<Type::Dynamic, Type::Dynamic, T>& operator-= (U rhs);
		template <typename U>
		Mat<Type::Dynamic, Type::Dynamic, T>& operator-= (const Mat<Type::Dynamic, Type::Dynamic, U>& rhs);
		template <typename U>
		Mat<Type::Dynamic, Type::Dynamic, T>& operator*= (U rhs);
		template <typename U>
		Mat<Type::Dynamic, Type::Dynamic, T>& operator*= (const Mat<Type::Dynamic, Type::Dynamic, U>& rhs);
		template <typename U>
		Mat<Type::Dynamic, Type::Dynamic, T>& operator/= (U rhs);
		template <typename U>
		Mat<Type::Dynamic, Type::Dynamic, T>& operator/= (const Mat<Type::Dynamic, Type::Dynamic, U>& rhs);
	};

	typedef Mat<2, 2, float> Mat2;
	typedef Mat<3, 3, float> Mat3;
	typedef Mat<4, 4, float> Mat4;
	typedef Mat<2, 2, double> DMat2;
	typedef Mat<3, 3, double> DMat3;
	typedef Mat<4, 4, double> DMat4;
	typedef Mat<2, 2, int> IMat2;
	typedef Mat<3, 3, int> IMat3;
	typedef Mat<4, 4, int> IMat4;
	typedef Mat<2, 2, unsigned int> UMat2;
	typedef Mat<3, 3, unsigned int> UMat3;
	typedef Mat<4, 4, unsigned int> UMat4;

	typedef Mat<2, 2, float> Mat2x2;
	typedef Mat<2, 3, float> Mat2x3;
	typedef Mat<2, 4, float> Mat2x4;
	typedef Mat<3, 2, float> Mat3x2;
	typedef Mat<3, 3, float> Mat3x3;
	typedef Mat<3, 4, float> Mat3x4;
	typedef Mat<4, 2, float> Mat4x2;
	typedef Mat<4, 3, float> Mat4x3;
	typedef Mat<4, 4, float> Mat4x4;
	typedef Mat<2, 2, double> DMat2x2;
	typedef Mat<2, 3, double> DMat2x3;
	typedef Mat<2, 4, double> DMat2x4;
	typedef Mat<3, 2, double> DMat3x2;
	typedef Mat<3, 3, double> DMat3x3;
	typedef Mat<3, 4, double> DMat3x4;
	typedef Mat<4, 2, double> DMat4x2;
	typedef Mat<4, 3, double> DMat4x3;
	typedef Mat<4, 4, double> DMat4x4;
	typedef Mat<2, 2, int> IMat2x2;
	typedef Mat<2, 3, int> IMat2x3;
	typedef Mat<2, 4, int> IMat2x4;
	typedef Mat<3, 2, int> IMat3x2;
	typedef Mat<3, 3, int> IMat3x3;
	typedef Mat<3, 4, int> IMat3x4;
	typedef Mat<4, 2, int> IMat4x2;
	typedef Mat<4, 3, int> IMat4x3;
	typedef Mat<4, 4, int> IMat4x4;
	typedef Mat<2, 2, unsigned int> UMat2x2;
	typedef Mat<2, 3, unsigned int> UMat2x3;
	typedef Mat<2, 4, unsigned int> UMat2x4;
	typedef Mat<3, 2, unsigned int> UMat3x2;
	typedef Mat<3, 3, unsigned int> UMat3x3;
	typedef Mat<3, 4, unsigned int> UMat3x4;
	typedef Mat<4, 2, unsigned int> UMat4x2;
	typedef Mat<4, 3, unsigned int> UMat4x3;
	typedef Mat<4, 4, unsigned int> UMat4x4;

	typedef Mat<Type::Dynamic, Type::Dynamic, float> MatX;
	typedef Mat<Type::Dynamic, Type::Dynamic, int> IMatX;
	typedef Mat<Type::Dynamic, Type::Dynamic, double> DMatX;
	typedef Mat<Type::Dynamic, Type::Dynamic, unsigned int> UMatX;

	// Static type operator
	template <size_t M, size_t N, typename T>
	constexpr Mat<M, N, T> operator+(const Mat<M, N, T>& r);
	template <size_t M, size_t N, typename T>
	Mat<M, N, T> operator-(const Mat<M, N, T>& r);
	template <size_t M, size_t N, typename T>
	Mat<M, N, T> operator+(const Mat<M, N, T>& l, const Mat<M, N, T>& r);
	template <size_t M, size_t N, typename T>
	Mat<M, N, T> operator-(const Mat<M, N, T>& l, const Mat<M, N, T>& r);
	template <size_t M, size_t N, typename T>
	Mat<M, N, T> operator+(const Mat<M, N, T>& l, T r);
	template <size_t M, size_t N, typename T>
	Mat<M, N, T> operator-(const Mat<M, N, T>& l, T r);
	template <size_t M, size_t N, typename T>
	Mat<M, N, T> operator+(T l, const Mat<M, N, T>& r);
	template <size_t M, size_t N, typename T>
	Mat<M, N, T> operator-(T l, const Mat<M, N, T>& r);
	template <size_t M, size_t N, typename T>
	Mat<M, N, T> operator*(const Mat<M, N, T>& l, T r);
	template <size_t M, size_t N, typename T>
	Mat<M, N, T> operator*(T l, const Mat<M, N, T>& r);
	template <size_t M, size_t N, typename T>
	Mat<M, N, T> operator/(const Mat<M, N, T>& l, T r);
	template <size_t M, size_t N, typename T>
	Mat<M, N, T> operator/(T l, const Mat<M, N, T>& r);
	template <size_t M, size_t N, typename T>
	Mat<M, N, T> operator/(const Mat<M, N, T>& l, const Mat<M, N, T>& r);

	template <size_t M, size_t N, typename T>
	Vec<N, T> operator*(const Mat<M, N, T>& l, const Vec<N, T>& r);
	template <size_t M, size_t K, size_t N, typename T>
	Mat<M, N, T> operator*(const Mat<M, K, T>& l, const Mat<K, N, T>& r);
	template <size_t M, size_t N, typename T>
	Mat<M, N, T> operator*(const Vec<M, T>& l, const Mat<1, N, T>& r);

	template <size_t M, size_t N, typename T>
	constexpr bool operator==(const Mat<M, N, T>& lhs, const Mat<M, N, T>& rhs);
	template <size_t M, size_t N, typename T>
	constexpr bool operator!=(const Mat<M, N, T>& lhs, const Mat<M, N, T>& rhs);

	template <size_t M, size_t N, typename T>
	std::ostream& operator<<(std::ostream& os, const Mat<M, N, T>& rhs);

	// Dynamic type operator
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator-(const Mat<Type::Dynamic, Type::Dynamic, T>& r);
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator+(const Mat<Type::Dynamic, Type::Dynamic, T>& l, const Mat<Type::Dynamic, Type::Dynamic, T>& r);
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator-(const Mat<Type::Dynamic, Type::Dynamic, T>& l, const Mat<Type::Dynamic, Type::Dynamic, T>& r);
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator+(const Mat<Type::Dynamic, Type::Dynamic, T>& l, T r);
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator-(const Mat<Type::Dynamic, Type::Dynamic, T>& l, T r);
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator+(T l, const Mat<Type::Dynamic, Type::Dynamic, T>& r);
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator-(T l, const Mat<Type::Dynamic, Type::Dynamic, T>& r);
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator*(const Mat<Type::Dynamic, Type::Dynamic, T>& l, T r);
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator*(T l, const Mat<Type::Dynamic, Type::Dynamic, T>& r);
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator/(const Mat<Type::Dynamic, Type::Dynamic, T>& l, T r);
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator/(T l, const Mat<Type::Dynamic, Type::Dynamic, T>& r);
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator/(const Mat<Type::Dynamic, Type::Dynamic, T>& l, const Mat<Type::Dynamic, Type::Dynamic, T>& r);

	template <typename T>
	Vec<Type::Dynamic, T> operator*(const Mat<Type::Dynamic, Type::Dynamic, T>& l, const Vec<Type::Dynamic, T>& r);
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator*(const Mat<Type::Dynamic, Type::Dynamic, T>& l, const Mat<Type::Dynamic, Type::Dynamic, T>& r);
	template <typename T>
	Mat<Type::Dynamic, Type::Dynamic, T> operator*(const Vec<Type::Dynamic, T>& l, const Mat<Type::Dynamic, Type::Dynamic, T>& r);

	template <typename T>
	constexpr bool operator==(const Mat<Type::Dynamic, Type::Dynamic, T>& lhs, const Mat<Type::Dynamic, Type::Dynamic, T>& rhs);

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const Mat<Type::Dynamic, Type::Dynamic, T>& rhs);
} // namespace MiniRenderer

// inline file
#include "Mat.inl"

#ifdef MATH_SIMD
	#include "Mat_simd.inl"
#endif // MATH_SIMD