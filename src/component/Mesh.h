#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

#include "math/Math.h"

namespace MiniRenderer
{
	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(const std::string& filename);
	public:
		void LoadObj(const std::string& filename);
	public:
		int GetVertexCount() const { return m_vertices.size(); }
	private:
		std::vector<Vec3> m_vertices;
		std::vector<Vec2> m_texcoords;
		std::vector<Vec3> m_normals;
		std::vector<Vec3> m_tangents;

		std::vector<UVec3> m_indices;
	};
}