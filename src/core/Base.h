#pragma once

namespace MiniRenderer
{
	enum DataType
	{
		Triangles,
		TriangleStrip,
		TriangleFan
	};

	enum DrawType
	{
		FACE,
		LINE
	};

	enum FaceCull
	{
		CullNone,
		CullFront,
		CullBack
	};
} // namespace MiniRenderer