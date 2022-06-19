#pragma once

#include "math/type/Base.h"
#include "math/type/Vec.h"
#include "math/type/Mat.h"
#include "math/type/Quat.h"

#include "Func.h"

namespace MiniRenderer::Math
{
	template <typename T>
	Mat<4, 4, T> Translate(const Mat<4, 4, T>& t, T x, T y, T z);
	template <typename T>
	Mat<4, 4, T> Translate(const Mat<4, 4, T>& t, const Vec<3, T>& v);
	template <typename T>
	Mat<4, 4, T> Translate(const Mat<4, 4, T>& t, const Vec<4, T>& v);

	template <typename T>
	Mat<3, 3, T> Rotate(const Mat<3, 3, T>& t, T angle, const Vec<3, T>& v);
	template <typename T>
	Mat<4, 4, T> Rotate(const Mat<4, 4, T>& t, T angle, const Vec<3, T>& v);
	template <typename T>
	Quat Rotate(const Quat& t, T angle, const Vec<3, T>& v);

	template <typename T>
	Mat<3, 3, T> Scale(const Mat<3, 3, T>& t, T x, T y, T z);
	template <typename T>
	Mat<3, 3, T> Scale(const Mat<3, 3, T>& t, const Vec<3, T>& v);
	template <typename T>
	Mat<4, 4, T> Scale(const Mat<4, 4, T>& t, T x, T y, T z);
	template <typename T>
	Mat<4, 4, T> Scale(const Mat<4, 4, T>& t, const Vec<3, T>& v);

	template <typename T>
	Mat<3, 3, T> PScale(const Mat<3, 3, T>& t, T ps);
	template <typename T>
	Mat<4, 4, T> PScale(const Mat<4, 4, T>& t, T ps);

	template <typename T>
	Mat<4, 4, T> LookAt(const Vec<3, T>& eye, const Vec<3, T>& focal, const Vec<3, T>& up);

	template <typename T>
	Mat<4, 4, T> Perspective(T fov, T aspect, T zNear, T zFar);

	template <typename T>
	Mat<4, 4, T> Orthogonal(T width, T height, T zNear, T zFar);
} // namespace MiniRenderer

// inline file
#include "Transform.inl"