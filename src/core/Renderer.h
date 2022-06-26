#pragma once

#include <memory>

#include "Rasterizer.h"
#include "Screen.h"
#include "Shader.h"

#include "math/Math.h"

#include "tool/Profiler.h"
#include "tool/Time.h"

#include "component/Camera.h"

namespace MiniRenderer
{
	class Renderer
	{
	public:
		using UpdateFunc = std::function<void(void)>;
	public:
		UpdateFunc Update;
	public:
		Renderer(int width = 800, int height = 600);
		inline Rasterizer* GetPtrRasterizer();
		inline Screen* GetPtrScreen();
		inline Profiler* GetPtrProfiler();
		inline Camera* GetPtrCamera();

		Camera& GetCamera() { return *m_camera.get(); }
		Rasterizer& GetRasterizer() { return m_rasterizer; }

		Camera& AddCamera();
		void AddCamera(std::shared_ptr<Camera> camera);

		void Run();
	public:
		template SHADER_DATA_TEMPLATE
		void DrawCall(const Shader SHADER_DATA_TYPE& shader, VertexInput* vertices, int vertexCount,
			VertexIndex* indices = nullptr, int indexCount = 0)
		{
			m_rasterizer.DrawCall(shader, vertices, vertexCount, indices, indexCount);
		}
	private:
		Rasterizer m_rasterizer;
		Screen m_screen;
		Profiler m_profiler;

		std::shared_ptr<Camera> m_camera;
	};
} // namespace MiniRenderer