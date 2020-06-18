#pragma once
#include "stdafx.h"
class Manager;

class PlayerManager
{
public:
	PlayerManager(Manager* manager);
	void draw();
	void createPlayer();
private:
	void createGun();
private:
	Manager* _manager;
};

typedef std::shared_ptr<PlayerManager> PlayerManagerPtr;
