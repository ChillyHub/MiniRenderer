#pragma once

#include <chrono>

namespace MiniRenderer
{
	class Time
	{
	public:
		static double GetTime();
		static double GetTimeSeconds();
		static double GetTimeMilliseconds();
		static double GetTimeMicroseconds();
		static double DeltaTime();
		static void UpdateTime();
		static void ResetTime();
	private:
		static std::chrono::time_point<std::chrono::steady_clock> s_startTime;
		static std::chrono::time_point<std::chrono::steady_clock> s_lastTime;
	};
}