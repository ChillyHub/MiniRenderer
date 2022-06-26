#include "Time.h"

namespace MiniRenderer
{
	std::chrono::time_point<std::chrono::steady_clock> 
		Time::s_startTime = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> 
		Time::s_lastTime = std::chrono::steady_clock::now();

	double Time::GetTime()
	{
		return GetTimeSeconds();
	}

	double Time::GetTimeSeconds()
	{
		return GetTimeMicroseconds() * 0.000001;
	}

	double Time::GetTimeMilliseconds()
	{
		return GetTimeMicroseconds() * 0.001;
	}

	double Time::GetTimeMicroseconds()
	{
		auto currentTime = std::chrono::steady_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(s_startTime).time_since_epoch();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(currentTime).time_since_epoch();
		return end.count() - start.count();
	}

	double Time::DeltaTime()
	{
		return 0.0;
	}

	void Time::UpdateTime()
	{
		s_lastTime = std::chrono::steady_clock::now();
	}

	void Time::ResetTime()
	{
		s_startTime = std::chrono::steady_clock::now();
		s_lastTime = s_startTime;
	}
} // namespace MiniRenderer
