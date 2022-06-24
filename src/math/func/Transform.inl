#pragma once

#include "Transform.h"

namespace MiniRenderer::Math
{
	// Translate ---------------------------------------------------------------
	// -------------------------------------------------------------------------
	template <typename T>
	inline Mat<4, 4, T> Translate(const Mat<4, 4, T>& t, T x, T y, T z)
	{
		Mat<4, 4, T> mat(t);
		mat[3] = { x, y, z, 1 };
		return mat;
	}

	template <typename T>
	inline Mat<4, 4, T> Translate(const Mat<4, 4, T>& t, const Vec<3, T>& v)
	{
		Mat<4, 4, T> mat(t);
		mat[3] = { v.x, v.y, v.z, 1 };
		return mat;
	}

	template <typename T>
	inline Mat<4, 4, T> Translate(const Mat<4, 4, T>& t, const Vec<4, T>& v)
	{
		Mat<4, 4, T> mat(t);
		mat[3] = v;
		return mat;
	}

	// Rotate ------------------------------------------------------------------
	// -------------------------------------------------------------------------
	template <typename T>
	inline Mat<3, 3, T> Rotate(const Mat<3, 3, T>& t, T angle, const Vec<3, T>& v)
	{
		T c = Cos(angle);
		T s = Sin(angle);
		T oneminusc = 1 - c;

		auto n = Normailzed(v);
		T x = n.x;
		T y = n.y;
		T z = n.z;

		Mat<3, 3, T> mat;
		mat[0][0] = x * x * oneminusc + c;
		mat[0][1] = x * y * oneminusc + z * s;
		mat[0][2] = x * z * oneminusc - y * s;

		mat[1][0] = x * y * oneminusc - z * s;
		mat[1][1] = y * y * oneminusc + c;
		mat[1][2] = y * z * oneminusc + x * s;

		mat[2][0] = x * z * oneminusc + y * s;
		mat[2][1] = y * z * oneminusc - x * s;
		mat[2][2] = z * z * oneminusc + c;

		return mat;
	}

	template <typename T>
	inline Mat<4, 4, T> Rotate(const Mat<4, 4, T>& t, T angle, const Vec<3, T>& v)
	{
		Mat<4, 4, T> mat(Rotate(Mat<3, 3, T>(), angle, v));
		mat[3] = t[3];
		return mat;
	}

	template <typename T>
	inline Quat Rotate(const Quat& t, T angle, const Vec<3, T>& v)
	{
		auto vv = v;
		
		float norm = Norm(t);
		if (norm > 1.0001f)
		{
			vv = Normailzed(vv);
		}

		float cos = Cos(angle * 0.5f);
		float sin = Sin(angle * 0.5f);

		return t * Quat(cos, sin * vv.x, sin * vv.y, sin * vv.z);
	}

	template <typename T>
	inline Vec<3, T> Rotate(const Quat& t, const Vec<3, T>& v)
	{
		Quat p = Quat(0.0f, Vec3(v));
		Quat q = t * p * t.inverse();
		return Vec<3, T>(q.x, q.y, q.z);
	}

	// Scale -------------------------------------------------------------------
	// -------------------------------------------------------------------------
	template <typename T>
	inline Mat<3, 3, T> Scale(const Mat<3, 3, T>& t, T x, T y, T z)
	{
		Mat<3, 3, T> mat;
		mat[0] = t[0] * x;
		mat[1] = t[1] * y;
		mat[2] = t[2] * z;
		return mat;
	}

	template <typename T>
	inline Mat<3, 3, T> Scale(const Mat<3, 3, T>& t, const Vec<3, T>& v)
	{
		Mat<3, 3, T> mat;
		mat[0] = t[0] * v.x;
		mat[1] = t[1] * v.y;
		mat[2] = t[2] * v.z;
		return mat;
	}

	template <typename T>
	inline Mat<4, 4, T> Scale(const Mat<4, 4, T>& t, T x, T y, T z)
	{
		Mat<4, 4, T> mat;
		mat[0] = t[0] * x;
		mat[1] = t[1] * y;
		mat[2] = t[2] * z;
		mat[3] = t[3];
		return mat;
	}

	template <typename T>
	inline Mat<4, 4, T> Scale(const Mat<4, 4, T>& t, const Vec<3, T>& v)
	{
		Mat<4, 4, T> mat;
		mat[0] = t[0] * v.x;
		mat[1] = t[1] * v.y;
		mat[2] = t[2] * v.z;
		mat[3] = t[3];
		return mat;
	}

	// PScale ------------------------------------------------------------------
	// -------------------------------------------------------------------------
	template <typename T>
	inline Mat<3, 3, T> PScale(const Mat<3, 3, T>& t, T ps)
	{
		Mat<3, 3, T> mat;
		mat[0] = t[0] * ps;
		mat[1] = t[1] * ps;
		mat[2] = t[2] * ps;
		return mat;
	}

	template <typename T>
	inline Mat<4, 4, T> PScale(const Mat<4, 4, T>& t, T ps)
	{
		Mat<4, 4, T> mat;
		mat[0] = t[0] * ps;
		mat[1] = t[1] * ps;
		mat[2] = t[2] * ps;
		mat[3] = t[3];
		return mat;
	}

	// LookAt ------------------------------------------------------------------
	// -------------------------------------------------------------------------
	template <typename T>
	inline Mat<4, 4, T> LookAt(const Vec<3, T>& eye, const Vec<3, T>& focal, const Vec<3, T>& up)
	{
		Vec<3, T> front(Normailzed(focal - eye));
		Vec<3, T> right;

		if (Norm2(Cross(front, up)) < 0.00001f)
		{
			right = Vec3{ 1.0f, 0.0f, 0.0f };
		}
		else
		{
			right = Normailzed(Cross(front, up));
		}
		
		Vec<3, T> top(Cross(right, front));

		Mat<4, 4, T> mat;
		mat[0][0] = right.x;
		mat[0][1] = top.x;
		mat[0][2] = -front.x;
		mat[1][0] = right.y;
		mat[1][1] = top.y;
		mat[1][2] = -front.y;
		mat[2][0] = right.z;
		mat[2][1] = top.z;
		mat[2][2] = -front.z;
		mat[3][0] = -Dot(right, eye);
		mat[3][1] = -Dot(top, eye);
		mat[3][2] = Dot(front, eye);
		mat[3][3] = 1;

		return mat;
	}

	// Perspective -------------------------------------------------------------
	// -------------------------------------------------------------------------
	template <typename T>
	inline Mat<4, 4, T> Perspective(T fov, T aspect, T zNear, T zFar)
	{
		T cot = Cot(fov / T(2));

		Mat<4, 4, T> mat;
		mat[0][0] = cot / aspect;
		mat[1][1] = cot;
		mat[2][2] = (zNear + zFar) / (zNear - zFar);
		mat[2][3] = T(-1);
		mat[3][2] = 2 * zNear * zFar / (zNear - zFar);

		return mat;
	}

	// Translate ---------------------------------------------------------------
	// -------------------------------------------------------------------------
	template <typename T>
	inline Mat<4, 4, T> Orthogonal(T width, T height, T zNear, T zFar)
	{
		Mat<4, 4, T> mat;
		mat[0][0] = T(1) / width;
		mat[1][1] = T(1) / height;
		mat[2][2] = -T(2) / (zFar - zNear);
		mat[3][2] = (zFar + zNear) / (zNear - zFar);
		mat[3][3] = T(1);

		return mat;
	}
} // namespace MiniRenderer