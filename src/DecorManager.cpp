#include "stdafx.h"
#include "DecorManager.h"
#include "Node.h"
#include "Transform.h"
#include "Cloud.h"
#include "ECS.h"

DecorManager::DecorManager(Manager* manager) : _manager(manager)
{
}

const Entity& DecorManager::createStaticObject(const std::string texture, const FPoint& position, GROUP layer)
{
	auto& staticObject = _manager->addEntity();
	auto& node = staticObject.addComponent<Node>();
	node.setTexture(texture);
	staticObject.getComponent<Transform>().setPosition(position);
	staticObject.addGroup(layer);
	return staticObject;
}

void DecorManager::createBackground(const std::string texture)
{
	const FPoint& pos = FPoint(Render::device.Width() / 2.0f, Render::device.Height() / 2.0f);
	createStaticObject(texture,pos, BACKGROUND);
	createClouds();
}

void DecorManager::createClouds()
{
	createCloud("cloud_1", FPoint(-50,650),FPoint(800, 650),25);
	createCloud("cloud_1", FPoint(-550,700),FPoint(800, 700),25);
	
	createCloud("cloud_2", FPoint(-150,600),FPoint(800, 600),40);
	createCloud("cloud_2", FPoint(-250,500),FPoint(800, 500),40);
	
	createCloud("cloud_3", FPoint(-550,550),FPoint(800, 550),30);
	createCloud("cloud_3", FPoint(-150,650),FPoint(800, 650),30);
	
	createCloud("cloud_4", FPoint(-10,500),FPoint(800, 500),22);
	createCloud("cloud_4", FPoint(-100,710),FPoint(800, 710),22);
}

void DecorManager::createCloud(std::string texture, const FPoint& startPosition, const FPoint& endPosition, float _time)
{
	auto& object = _manager->addEntity();
	auto& node = object.addComponent<Node>();
	node.setTexture(texture);
	auto& cloud = object.addComponent<Cloud>();
	cloud.setPositions(startPosition, endPosition, _time);
}

void DecorManager::createStand(const std::string texture)
{
	const FPoint& pos = FPoint(Render::device.Width() / 2.0f, 0.0);
	auto& stand = createStaticObject(texture, pos, DECORS);
	auto& transform = stand.getComponent<Transform>();
	transform.setAnchor(0.5, 0);
	transform.setScale(0.25f);
	 
}

void DecorManager::draw()
{
	for (const auto  e : _manager->getGroup(BACKGROUND))
	{
		e->draw();
	}
	for (const auto  e : _manager->getGroup(DECORS))
	{
		e->draw();
	}
}