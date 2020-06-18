#include "stdafx.h"
#include "Aim.h"

void Aim::init()
{
	if (!entity->hasComponent<Transform>())
	{
		entity->addComponent<Transform>();
	}
	_transform = &entity->getComponent<Transform>();
	_transform->setPosition(Render::device.Width() / 2.0f, Render::device.Height() / 2.0f);
	_transform->setScale(0.5f);
	
	if (!entity->hasComponent<Node>())
	{
		entity->addComponent<Node>();
	}
	
	_node = &entity->getComponent<Node>();
	_node->setTexture("aim");

	entity->addGroup(PLAYER);
}

void Aim::mouseMove(const IPoint& mousePos)
{
	_transform->setPosition(mousePos.x,mousePos.y);
}