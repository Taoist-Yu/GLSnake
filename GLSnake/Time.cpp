#include "Time.h"
#include<time.h>

Timer Time;

Timer::Timer()
	: time(0), timeScale(1), deltaTime(0)
{
}

Timer::~Timer()
{
}

float Timer::GetTime()
{
	return time * timeScale;
}

float Timer::GetDeltaTime()
{
	return deltaTime * timeScale;
}

float Timer::GetTimeScale()
{
	return timeScale;
}

float Timer::GetUnscaledTime()
{
	return time;
}

float Timer::GetUnscaledDeltaTime()
{
	return deltaTime;
}

void Timer::SetTimeScale(float timeScale)
{
	this->timeScale = timeScale;
}

void Timer::TimerUpdate()
{
	float newTime = (float)clock() / 1000;
	deltaTime = newTime - time;
	time = newTime;
}
