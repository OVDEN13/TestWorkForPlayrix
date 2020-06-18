#include "stdafx.h"
#include "LifeTimer.h"

void LifeTimer::setDelay(double time)
{
	setTime(time);
	setCallback([=]()
		{
			destroyYourself();
		});
	play();
}

void LifeTimer::destroyYourself()
{
	entity->destroy();
}