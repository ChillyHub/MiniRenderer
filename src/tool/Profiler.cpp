#include "Profiler.h"

#include "MiniRenderer.h"

namespace MiniRenderer
{	
	float Profiler::GetFPS() const
	{
		return m_fps;
	}

	void Profiler::UpdateFPS()
	{
		auto currentTime = Time::GetTime();
		auto deltaTime = currentTime - m_lastFrameTime;
		m_frameCount++;

		if (deltaTime > 1.0)
		{
			m_fps = m_frameCount / deltaTime;
			m_lastFrameTime = currentTime;
			m_frameCount = 0;
		}
	}

}