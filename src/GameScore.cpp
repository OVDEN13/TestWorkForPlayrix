#include "stdafx.h"
#include "GameScore.h"

void GameScore::init()
{
	_score = 0;
	if (!entity->hasComponent<Transform>())
	{
		entity->addComponent<Transform>();
	}
	
	if (!entity->hasComponent<TextNode>())
	{
		entity->addComponent<TextNode>();
	}
	_textNode = &entity->getComponent<TextNode>();
 
	entity->addGroup(GROUP_NAME::UI);
	entity->addGroup(GROUP_NAME::GAME_SCORE);
}

void GameScore::update(float dt)
{
	_textNode->setText(std::to_string(_score));
}

void GameScore::resetScore()
{
	_score = 0;
}

void GameScore::addScore(int count)
{
	_score += count;
}

void GameScore::reduceScore(int count)
{
	_score = _score - count < 0 ? 0 : count;
}

int GameScore::getScore()
{
	return _score;
}