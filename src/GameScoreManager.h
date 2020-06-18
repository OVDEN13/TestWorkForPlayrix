#pragma once
class Manager;
class Entity;

class GameScoreManager
{
public:
	GameScoreManager(Manager* manager);
	void changedState();
	const Entity& getGameScore();
private:
	void init();
private:
	Manager* _manager;
};

typedef std::shared_ptr<GameScoreManager> GameScoreManagerPtr;