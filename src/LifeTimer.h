#pragma once

#include "Timer.h"

class LifeTimer : public Timer
{
public:
	void setDelay(double time);
	void destroyYourself();
private:
	Timer* _timer;
};