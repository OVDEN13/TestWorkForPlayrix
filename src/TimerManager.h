#pragma once
class Manager;
class Entity;

class TimerManager
{
public:
	TimerManager(Manager* manager);
	void changedState();
	const Entity& createGameTimer();
private:
	Manager* _manager;
};

typedef std::shared_ptr<TimerManager> TimerManagerPtr;