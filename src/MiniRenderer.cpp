#include "MiniRenderer.h"

#include <iostream>

namespace MiniRenderer
{
	Renderer::Renderer(int width, int height)
		: m_rasterizer(Rasterizer(width, height, this))
		, m_screen(Screen()) , m_profiler(Profiler())
	{
		try
		{
			m_screen.Init(TEXT("MiniRenderer"), this, width, height);
		}
		catch (const std::exception& e)
		{
			std::cerr << "ERROR::" << e.what() << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	//Rasterizer* Renderer::GetPtrRasterizer()
	//{
	//	return &m_rasterizer;
	//}
	//
	//Screen* Renderer::GetPtrScreen()
	//{
	//	return &m_screen;
	//}

	void Renderer::Run()
	{
		try
		{
			m_screen.Show();
			
			while (m_screen.ShouldRun())
			{
				m_profiler.UpdateFPS();

				Update();

				m_screen.Update();
				//Sleep(1);
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << "ERROR::" << e.what() << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}
