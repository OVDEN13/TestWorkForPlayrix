#include "stdafx.h"
#include "Cloud.h"
#include "GameManager.h"

void Cloud::init()
{
	if (!entity->hasComponent<Transform>())
	{
		entity->addComponent<Transform>();
	}
	_transform = &entity->getComponent<Transform>();
	
	if (!entity->hasComponent<Node>())
	{
		entity->addComponent<Node>();
	}
	_node = &entity->getComponent<Node>();
	
	_startPos = FPoint();
	_endPos = FPoint();
	_speed = FPoint();
 
	entity->addGroup(GROUP_NAME::DECORS);
}

void Cloud::setPositions(FPoint position, FPoint endPosition, float time)
{
	_startPos = position;
	_transform->setPosition(_startPos);
	_endPos = endPosition;
	float speed = _startPos.GetDistanceTo(_endPos) / time;
	FPoint dir =   _endPos - _startPos;
	dir.Normalize();
	_speed = dir * speed ;
}

void Cloud::update(float dt)
{
	if (GameStateManagerI->getGameState() == GameState::Playing)
	{
		if (_transform->getPosition().x < _endPos.x) {
			_transform->setPosition(_transform->getPosition() + (_speed * dt));
		}
		else {
			_transform->setPosition(_startPos);
		}
	}
}
