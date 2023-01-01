#pragma once

#include <time.h>
#include <chrono>


namespace Core::Time
{
	class Timer
	{
	public:
		Timer(unsigned int width, unsigned int height);
		~Timer();

		void Update();

		double GetDeltaTime();
		std::chrono::time_point<std::chrono::system_clock> start, end;
		std::chrono::duration<double> elapsedMono;
		std::chrono::duration<double> elapsedMulti;

		bool begin;
		bool timerDone = false;

		unsigned int width;
		unsigned int height;

		void ChronoBegin();
		void ChronoEnd(std::chrono::duration<double> &elapsed);

	private:
		double _deltaTime = 0;
		double _currentFrame = 0; 
		double _lastFrame = 0;
	};

}
