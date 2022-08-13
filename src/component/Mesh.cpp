#include "Mesh.h"

namespace MiniRenderer
{
	Mesh::Mesh(const std::string& filename)
	{
		LoadObj(filename);
	}
	
	void Mesh::LoadObj(const std::string& filename)
	{
		std::ifstream file(filename);

		if (!file.is_open())
		{
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Failed to open file " + filename);
		}

		std::string line;
		while (!file.eof())
		{
			std::string info;
			std::getline(file, line);
			std::stringstream ss(line);
			if (!line.compare(0, 2, "v "))
			{
				Vec3 v;
				ss >> info;
				ss >> v.x;
				ss >> v.y;
				ss >> v.z;
				m_vertices.push_back(v);
			}
			else if (!line.compare(0, 3, "vt "))
			{
				Vec2 vt;
				ss >> info;
				ss >> vt.x;
				ss >> vt.y;
				m_texcoords.push_back(vt);
			}
			else if (!line.compare(0, 3, "vn "))
			{
				Vec3 vn;
				ss >> info;
				ss >> vn.x;
				ss >> vn.y;
				ss >> vn.z;
				m_normals.push_back(vn);
			}
			else if (!line.compare(0, 2, "f "))
			{
				int index;
				ss >> info;
				for (int i = 0; i < 3; ++i)
				{
					std::string str;
					ss >> str;
					std::stringstream sss(str);
					
					UVec3 indices;
					sss >> index;
					indices.x = index;
					sss >> index;
					sss >> index;
					indices.y = index;
					sss >> index;
					sss >> index;
					indices.z = index;

					m_indices.push_back(indices);
				}
			}
		}
	}
}