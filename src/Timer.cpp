#include "stdafx.h"
#include "Timer.h"

void Timer::init()
{
	_initTime = 60.0;
	_time = _initTime;
	_active = false;
	_loop = false;
	_callback = nullptr;
}

void Timer::setLoop()
{
	_loop = true;
}

void Timer::setTime(double time)
{
	_time = time;
}

void Timer::setInitTime(double time, bool needReset)
{
	_initTime = time;
	if(needReset)
	{
		resetTimer();
	}
}

void Timer::update(float dt)
{
	if(_active)
	{
		_time -= dt;
		if(_time <= 0.0 && _callback)
		{
			if (_loop)
			{
				_time = _initTime;
			} else
			{
				pause();
				_time = 0.0f;
			}
			_callback();
		}
	}
}

void Timer::resetTimer()
{
	_time = _initTime;
	_active = false;
}

void Timer::pause()
{
	_active = false;
}

void Timer::play()
{
	_active = true;
}

double Timer::getTime()
{
	return _time;
}

void Timer::setCallback(CallbackVoid callback)
{
	_callback = callback;
}