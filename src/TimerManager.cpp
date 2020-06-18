#include "stdafx.h"
#include "TimerManager.h"
#include "GameManager.h"
#include "ECS.h"
#include "GameTimer.h"
#include "TextNode.h"
#include "Timer.h"
#include "Transform.h"

TimerManager::TimerManager(Manager* manager) : _manager(manager)
{
	
}

void TimerManager::changedState()
{
	switch (GameStateManagerI->getGameState())
	{
	case GameState::Menu:
		for (const auto e : _manager->getGroup(GAME_TIMER))
		{
			if (e->hasComponent<Timer>())
			{
				e->getComponent<Timer>().resetTimer();
			}
		}
		break;
	case GameState::Playing:
		for (const auto e : _manager->getGroup(GAME_TIMER))
		{
			if (e->hasComponent<Timer>())
			{
				e->getComponent<Timer>().play();
			}
		}
		break;
	case GameState::Pause:
	case GameState::Finish:
		for (const auto e : _manager->getGroup(GAME_TIMER))
		{
			if (e->hasComponent<Timer>())
			{
				e->getComponent<Timer>().pause();
			}
		}
		break;
	}
}

const Entity& TimerManager::createGameTimer()
{
	const auto& gameConfig = AssetsManagerI->getStaticGameConfig();
	
	auto position = FPoint(Render::device.Width() / 2, Render::device.Height() -10);
	CallbackVoid callback = []()
	{
		GameStateManagerI->setGameState(GameState::Finish);
	};
	
	auto& gameTimer = _manager->addEntity();
	auto& transform = gameTimer.addComponent<Transform>();
	auto& timer = gameTimer.addComponent<Timer>();
	gameTimer.addComponent<TextNode>();
	gameTimer.addComponent<GameTimer>();
	
	timer.setInitTime(gameConfig.time, true);
	timer.setCallback(callback);
 
	transform.setPosition(position);
	transform.setScale(1.5f);
	return gameTimer;
}
