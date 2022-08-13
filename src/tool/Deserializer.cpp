#include "Deserializer.h"

namespace MiniRenderer
{
	namespace Load
	{
		Mesh LoadObj(const std::string& filename)
		{
			Mesh mesh;
			mesh.LoadObj(filename);
			return mesh;
		}
	}
}