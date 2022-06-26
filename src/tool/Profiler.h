#pragma once

#include "Time.h"

namespace MiniRenderer
{
	class Profiler
	{
	public:
		float GetFPS() const;
		void UpdateFPS();
	private:
		float m_fps = 0.0f;
		float m_lastFrameTime = 0.0f;
		int m_frameCount = 0;
	};
} // namespace MiniRenderer