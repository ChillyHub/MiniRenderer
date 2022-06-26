#pragma once

#include <vector>

#include "math/Math.h"
#include "core/Base.h"

namespace MiniRenderer
{
	class Sphere
	{
	public:
		Sphere();
    public:
        Vec3 GetVertex(int i) const;
        Vec2 GetUV(int i) const;
        Vec3 GetNormal(int i) const;
        unsigned int GetIndex(int i) const;
        std::vector<unsigned int> GetIndices() const;
        unsigned int GetIndexCount() const;
        unsigned int GetVertexCount() const;
        DataType GetDataType() const;
	private:
		std::vector<Vec3> vertices;
		std::vector<Vec2> uv;
		std::vector<Vec3> normals;

        std::vector<unsigned int> indices;
        unsigned int indexCount;
        unsigned int vertexCount;
        DataType dataType = DataType::TriangleStrip;
    private:
        const unsigned int X_SEGMENTS = 64;
        const unsigned int Y_SEGMENTS = 64;
	};

    Sphere::Sphere()
    {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
            {
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                float xPos = Math::Cos(xSegment * 2.0f * PI) * Math::Sin(ySegment * PI);
                float yPos = Math::Cos(ySegment * PI);
                float zPos = Math::Sin(xSegment * 2.0f * PI) * Math::Sin(ySegment * PI);

                vertices.push_back(Vec3(xPos, yPos, zPos));
                uv.push_back(Vec2(xSegment, ySegment));
                normals.push_back(Vec3(xPos, yPos, zPos));
            }
        }

        bool oddRow = false;
        for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                }
            }
            else
            {
                for (int x = X_SEGMENTS; x >= 0; --x)
                {
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                }
            }
            oddRow = !oddRow;
        }
        indexCount = indices.size();
        vertexCount = vertices.size();
    }

    inline Vec3 Sphere::GetVertex(int i) const
    {
        return vertices[i];
    }

    inline Vec2 Sphere::GetUV(int i) const
    {
        return uv[i];
    }

    inline Vec3 Sphere::GetNormal(int i) const
    {
        return normals[i];
    }

    inline unsigned int Sphere::GetIndex(int i) const
    {
        return indices[i];
    }

    inline std::vector<unsigned int> Sphere::GetIndices() const
    {
        return indices;
    }

    inline unsigned int Sphere::GetIndexCount() const
    {
        return indexCount;
    }

    inline unsigned int Sphere::GetVertexCount() const
    {
        return vertexCount;
    }

    inline DataType Sphere::GetDataType() const
    {
        return dataType;
    }
} // namespace MiniRenderer