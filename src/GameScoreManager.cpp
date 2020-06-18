#include "stdafx.h"
#include "GameScoreManager.h"
#include "GameManager.h";
#include "GameScore.h"
#include "ECS.h"

GameScoreManager::GameScoreManager(Manager* manager) : _manager(manager)
{
	init();
}

void GameScoreManager::changedState()
{
	switch (GameStateManagerI->getGameState())
	{
		case GameState::Menu:
			for (const auto e : _manager->getGroup(GROUP_NAME::GAME_SCORE))
			{
				e->getComponent<GameScore>().resetScore();
			}
			break;
	}
}

const Entity& GameScoreManager::getGameScore()
{
	const Entity* gameScore = _manager->getGroup(GROUP_NAME::GAME_SCORE).at(0);
	return *gameScore;
}

void GameScoreManager::init()
{
	auto position = FPoint(Render::device.Width() - 150, Render::device.Height() - 10);
	auto& gameScore = _manager->addEntity();
	auto& transform = gameScore.addComponent<Transform>();
	transform.setPosition(position);
	auto& score = gameScore.addComponent<GameScore>();
}