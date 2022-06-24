#pragma once

#include <memory>

#include "core/Rasterizer.h"
#include "core/Screen.h"
#include "core/Shader.h"

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

		Camera& AddCamera();
		void AddCamera(std::shared_ptr<Camera> camera);

		void Run();
	public:
		template SHADER_DATA_TEMPLATE
		void DrawCall(VertexInput* vertices, int vertexCount, const Shader SHADER_DATA_TYPE& shader, VertexIndex* indices = nullptr)
		{
			m_rasterizer.DrawCall(vertices, vertexCount, shader, indices);
		}
	private:
		Rasterizer m_rasterizer;
		Screen m_screen;
		Profiler m_profiler;

		std::shared_ptr<Camera> m_camera;
	};
}