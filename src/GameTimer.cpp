#include "stdafx.h"
#include "GameTimer.h"

void GameTimer::init()
{	
	if (!entity->hasComponent<TextNode>())
	{
		entity->addComponent<TextNode>();
	}
	_textNode = &entity->getComponent<TextNode>();
	
	if (!entity->hasComponent<Timer>())
	{
		entity->addComponent<Timer>();
	}
	_timer = &entity->getComponent<Timer>();
	entity->addGroup(GROUP_NAME::GAME_TIMER);
}

void GameTimer::update(float dt)
{
	_textNode->setText(std::to_string(static_cast<int>(_timer->getTime())));
}