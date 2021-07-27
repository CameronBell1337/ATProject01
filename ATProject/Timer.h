#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	float ElapseTime(); //last time you called this function
	float PeekElapseTime() const; //Last time you called elapse time without reseting the point

private:
	std::chrono::steady_clock::time_point last;
};
