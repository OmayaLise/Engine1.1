#include "Timer.hpp"
#include <imgui.h>
#include <string.h>
#include <imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Core::Time
{
	Timer::Timer(unsigned int width, unsigned int height) 
		: width(width)
		, height(height)
	{
	}

	Timer::~Timer()
	{
	}

	void Timer::Update()
	{
		_currentFrame = glfwGetTime();
		_deltaTime = _currentFrame - _lastFrame;
		_lastFrame = _currentFrame;
	}

	double Timer::GetDeltaTime()
	{
		return _deltaTime;
	}

	void Timer::ChronoBegin()
	{
		start = std::chrono::system_clock::now();
	}

	void Timer::ChronoEnd(std::chrono::duration<double> &elapsed)
	{
		if (begin)
		{
			end = std::chrono::system_clock::now();

			elapsed = end - start;

			std::cout << "elapsed time: " << elapsed.count() << "s\n";
			timerDone = true;
		}
	}

}
