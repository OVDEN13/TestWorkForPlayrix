#pragma once
#include "stdafx.h"

class Manager;
class Entity;

class DecorManager
{
public:
	DecorManager(Manager* manager);

	const Entity& createStaticObject(const std::string texture, const FPoint& position, GROUP layer);
	
	void createBackground(const std::string texture);
	void createClouds();
	void createCloud(std::string texture, const FPoint& startPosition, const FPoint& endPosition, float _time);

	void createStand(const std::string texture);
	
	void draw();
private:
	Manager* _manager;
};

typedef std::shared_ptr<DecorManager> DecorManagerPtr;