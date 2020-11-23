#include "timer.hpp"

Timer::Timer(int FPS) : frameDelay{0}, deltaTime{0.0f}, lastFrame{0.0f}
{
	setFPS(FPS);
}

Timer::~Timer()
{}

void Timer::setFPS(int FPS)
{
	frameDelay = 1000 / FPS;
}

void Timer::setCurrentTime(float time)
{
	deltaTime = time - lastFrame;
	lastFrame = time;
}

int Timer::getSleepTime(float time)
{
	return frameDelay - (time - lastFrame);
}