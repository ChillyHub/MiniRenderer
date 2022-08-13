#pragma once

#include "Mat.h"

#include <xmmintrin.h>

namespace MiniRenderer
{
	// Mat operator STATIC ------------------------------
	// --------------------------------------------------
	template <>
	inline Vec<4, float> operator*(const Mat<4, 4, float>& l, const Vec<4, float>& r)
	{
		Vec<4, float> res;

		__m128 e0 = _mm_shuffle_ps(r.ds, r.ds, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(r.ds, r.ds, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(r.ds, r.ds, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(r.ds, r.ds, _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(l[0].ds, e0);
		__m128 m1 = _mm_mul_ps(l[1].ds, e1);
		__m128 m2 = _mm_mul_ps(l[2].ds, e2);
		__m128 m3 = _mm_mul_ps(l[3].ds, e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		res.ds = a2;

		return res;
	}

	template <>
	inline Mat<4, 4, float> operator*(const Mat<4, 4, float>& l, const Mat<4, 4, float>& r)
	{
		Mat<4, 4, float> res;
		{
			__m128 e0 = _mm_shuffle_ps(r[0].ds, r[0].ds, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 e1 = _mm_shuffle_ps(r[0].ds, r[0].ds, _MM_SHUFFLE(1, 1, 1, 1));
			__m128 e2 = _mm_shuffle_ps(r[0].ds, r[0].ds, _MM_SHUFFLE(2, 2, 2, 2));
			__m128 e3 = _mm_shuffle_ps(r[0].ds, r[0].ds, _MM_SHUFFLE(3, 3, 3, 3));

			__m128 m0 = _mm_mul_ps(l[0].ds, e0);
			__m128 m1 = _mm_mul_ps(l[1].ds, e1);
			__m128 m2 = _mm_mul_ps(l[2].ds, e2);
			__m128 m3 = _mm_mul_ps(l[3].ds, e3);

			__m128 a0 = _mm_add_ps(m0, m1);
			__m128 a1 = _mm_add_ps(m2, m3);
			__m128 a2 = _mm_add_ps(a0, a1);

			res[0].ds = a2;
		}

		{
			__m128 e0 = _mm_shuffle_ps(r[1].ds, r[1].ds, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 e1 = _mm_shuffle_ps(r[1].ds, r[1].ds, _MM_SHUFFLE(1, 1, 1, 1));
			__m128 e2 = _mm_shuffle_ps(r[1].ds, r[1].ds, _MM_SHUFFLE(2, 2, 2, 2));
			__m128 e3 = _mm_shuffle_ps(r[1].ds, r[1].ds, _MM_SHUFFLE(3, 3, 3, 3));

			__m128 m0 = _mm_mul_ps(l[0].ds, e0);
			__m128 m1 = _mm_mul_ps(l[1].ds, e1);
			__m128 m2 = _mm_mul_ps(l[2].ds, e2);
			__m128 m3 = _mm_mul_ps(l[3].ds, e3);

			__m128 a0 = _mm_add_ps(m0, m1);
			__m128 a1 = _mm_add_ps(m2, m3);
			__m128 a2 = _mm_add_ps(a0, a1);

			res[1].ds = a2;
		}

		{
			__m128 e0 = _mm_shuffle_ps(r[2].ds, r[2].ds, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 e1 = _mm_shuffle_ps(r[2].ds, r[2].ds, _MM_SHUFFLE(1, 1, 1, 1));
			__m128 e2 = _mm_shuffle_ps(r[2].ds, r[2].ds, _MM_SHUFFLE(2, 2, 2, 2));
			__m128 e3 = _mm_shuffle_ps(r[2].ds, r[2].ds, _MM_SHUFFLE(3, 3, 3, 3));

			__m128 m0 = _mm_mul_ps(l[0].ds, e0);
			__m128 m1 = _mm_mul_ps(l[1].ds, e1);
			__m128 m2 = _mm_mul_ps(l[2].ds, e2);
			__m128 m3 = _mm_mul_ps(l[3].ds, e3);

			__m128 a0 = _mm_add_ps(m0, m1);
			__m128 a1 = _mm_add_ps(m2, m3);
			__m128 a2 = _mm_add_ps(a0, a1);

			res[2].ds = a2;
		}

		{
			__m128 e0 = _mm_shuffle_ps(r[3].ds, r[3].ds, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 e1 = _mm_shuffle_ps(r[3].ds, r[3].ds, _MM_SHUFFLE(1, 1, 1, 1));
			__m128 e2 = _mm_shuffle_ps(r[3].ds, r[3].ds, _MM_SHUFFLE(2, 2, 2, 2));
			__m128 e3 = _mm_shuffle_ps(r[3].ds, r[3].ds, _MM_SHUFFLE(3, 3, 3, 3));

			__m128 m0 = _mm_mul_ps(l[0].ds, e0);
			__m128 m1 = _mm_mul_ps(l[1].ds, e1);
			__m128 m2 = _mm_mul_ps(l[2].ds, e2);
			__m128 m3 = _mm_mul_ps(l[3].ds, e3);

			__m128 a0 = _mm_add_ps(m0, m1);
			__m128 a1 = _mm_add_ps(m2, m3);
			__m128 a2 = _mm_add_ps(a0, a1);

			res[3].ds = a2;
		}

		return res;
	}
}