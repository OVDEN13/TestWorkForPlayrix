#include "stdafx.h"

#include "AssetsManager.h"
#include "Bomb.h"
#include "GameManager.h"
#include "Node.h"
#include "Target.h"
#include "ECS.h"

CONST INT INDENT_X = 50;
CONST INT INDENT_Y = 50;
CONST INT SAFE_TIME = 10;
CONST INT SPAWN_ZONE = 6;

TargetManager::TargetManager(Manager* manager) : _manager(manager), _timer(0), _isPlay(false)
{
	init();
}

void TargetManager::changedState()
{
	switch (GameStateManagerI->getGameState())
	{
		case GameState::Playing:
			_isPlay = true;
			createTargets();
			break;
		case GameState::Menu:
		case GameState::Pause:
			_isPlay = false;
			break;
		case GameState::Finish:
			_isPlay = false;
			for (const auto e : _manager->getGroup(TARGETS))
			{
				e->destroy();
			}
			break;
	}
}

void TargetManager::init()
{
	_gameConfig = AssetsManagerI->getStaticGameConfig();
	const int iterations = _gameConfig.iterations;
	const int maxTime = _gameConfig.time - SAFE_TIME;
	
	std::vector<TARGET_TYPE> targets;
	for(int i = 0; i < _gameConfig.countTarget; i++)
	{
		targets.push_back(TARGET_TYPE::CLASSIC);
	}
	for (int i = 0; i < _gameConfig.countBomb; i++)
	{
		targets.push_back(TARGET_TYPE::BOMB);
	}
	std::random_shuffle(targets.begin(), targets.end());
	
	std::vector<bool>  pos;
	int maxTarget = _gameConfig.countTarget + _gameConfig.countBomb;
	for(int i = 0; i < SPAWN_ZONE * iterations; i++)
	{
		maxTarget--;
		pos.push_back(maxTarget > 0);
	}
	std::random_shuffle(pos.begin(), pos.end());

	int timeInterval = maxTime / iterations;
	for(int i = iterations; i >=0 ; i--)
	{
		int index = 0;
		for(int s = 0; s < SPAWN_ZONE; s++)
		{
			index++;
			if(pos.at(s*i) == 1)
			{
				TargetData data;
				data.type = targets[s* index];
				data.spawnPos = getSpawnPosition(s);
				data.delayBeforeSpawn = i * timeInterval;
				_targetData.push_back(data);
			}
		}
	}
}

void TargetManager::draw()
{
	for (const auto e : _manager->getGroup(TARGETS))
	{
		if (e->hasComponent<Node>())
		{
			e->getComponent<Node>().draw();
		}
	}
}

void TargetManager::createTargets()
{
	for(const auto& data : _targetData)
	{
		makeTarget(data);
	}
}

void TargetManager::makeTarget(TargetData data)
{
	switch(data.type)
	{
		case TARGET_TYPE::CLASSIC:
			makeBaseTarget(data);
			break;
		case TARGET_TYPE::BOMB:
			makeBomb(data);
			break;
	}
}

void TargetManager::makeBaseTarget(TargetData data)
{
	auto& gameObject = _manager->addEntity();
	auto& baseTarget = gameObject.addComponent<Target>();
	baseTarget.setSpawnPosition(data.spawnPos, _gameConfig.targetSpeed);
	baseTarget.setDelay(data.delayBeforeSpawn);
	baseTarget.setTexture("target");
	gameObject.addGroup(TARGETS);
}

void TargetManager::makeBomb(TargetData data)
{
	auto& gameObject = _manager->addEntity();
	auto& baseTarget = gameObject.addComponent<Bomb>();
	baseTarget.setSpawnPosition(data.spawnPos, _gameConfig.targetSpeed);
	baseTarget.setDelay(data.delayBeforeSpawn);
	baseTarget.setTexture("bomb");
	gameObject.addGroup(TARGETS);
}

const FPoint& TargetManager::getSpawnPosition(int index)
{
	auto diapason = Render::device.Width() - INDENT_X * 2;
	auto segment = diapason / SPAWN_ZONE;
	return FPoint(INDENT_X + segment* index, Render::device.Height() + INDENT_Y);
}