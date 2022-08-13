#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

#include <component/Mesh.h>
#include <core/Texture.h>

namespace MiniRenderer
{
	namespace Load
	{
		Mesh LoadObj(const std::string& filename);
		Texture LoadTex(const std::string& filename);
	}
	
	class Deserializer
	{

	};
}