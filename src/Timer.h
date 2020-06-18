#pragma once
#include "Callback.h"
#include "ECS.h"

class Timer : public Component
{
public:
	void init() override;
	void update(float dt) override;

	void setLoop();
	void setTime(double time);
	void setInitTime(double time, bool needReset = false);
	void resetTimer();
	void pause();
	void play();
	double getTime();

	void setCallback(CallbackVoid callback);

private:
	bool _active;
	double  _initTime;
	double _time;
	bool _loop;
	
	CallbackVoid _callback;
};