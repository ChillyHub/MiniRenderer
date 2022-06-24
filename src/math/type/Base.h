#pragma once

#include <assert.h>

#include <iostream>
#include <cmath>
#include <initializer_list>

#define S(a) std::string(a)

#ifdef _MSC_VER
	#define _FUN_NAME_ __FUNCTION__
#else
	#define _FUN_NAME_ __func__
#endif

namespace MiniRenderer
{
	const float PI = 3.14159265358979323846264338327f;
	const float PI2 = PI * PI;
	const float PI_IV = 1.0f / PI;
	const float PI2_IV = 1.0f / PI2;

	const double d_PI = 3.14159265358979323846264338327;
	const double d_PI2 = d_PI * d_PI;
	const double d_PI_IV = 1.0f / d_PI;
	const double d_PI2_IV = 1.0f / d_PI2;

	enum Type : size_t
	{
		Dynamic = 0x0
	};
}