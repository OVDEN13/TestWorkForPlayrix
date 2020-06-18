#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager() : _assetsManager(nullptr) , _inputManager(nullptr), _playerManager(nullptr)
{

}

void GameManager::changedState()
{
	_uiManager->changedState();
	_timerManager->changedState();
	_bulletManager->changedState();
	_targetManager->changedState();
	_gameScoreManager->changedState();
	_effectManager->changedState();
}

void GameManager::init()
{
	initManager();
	initResources();
	initGame();
}

void GameManager::initManager()
{
	_assetsManager = std::make_shared<AssetsManager>();
	_gameStateManager = std::make_shared<GameStateManager>();
	_inputManager = std::make_shared<InputManager>(&_manager);
	_uiManager = std::make_shared<UIManager>(&_manager);
	_playerManager = std::make_shared<PlayerManager>(&_manager);
	_decorManager = std::make_shared<DecorManager>(&_manager);
	_timerManager = std::make_shared<TimerManager>(&_manager);
	_bulletManager = std::make_shared<BulletManager>(&_manager);
	_colliderManager = std::make_shared<ColliderManager>(&_manager);
	_targetManager = std::make_shared<TargetManager>(&_manager);
	_gameScoreManager = std::make_shared<GameScoreManager>(&_manager);
	_effectManager = std::make_shared<EffectManager>(&_manager);
}

void GameManager::initResources()
{
	_assetsManager->addTexture("aim");
	_assetsManager->addTexture("background");

	_assetsManager->addTexture("cloud_1");
	_assetsManager->addTexture("cloud_2");
	_assetsManager->addTexture("cloud_3");
	_assetsManager->addTexture("cloud_4");

	_assetsManager->addTexture("bomb");
	_assetsManager->addTexture("stand");
	_assetsManager->addTexture("cannon");
	_assetsManager->addTexture("cannonball");
	_assetsManager->addTexture("target");

	_assetsManager->addTexture("ButtonsStyle11_04");
	_assetsManager->addTexture("ButtonsStyle11_03");
	_assetsManager->addTexture("ButtonsStyle11_02");
	_assetsManager->addTexture("ButtonsStyle9_04");
	_assetsManager->addTexture("ButtonsStyle9_03");
	_assetsManager->addTexture("ButtonsStyle9_02");
}

void GameManager::initGame()
{
	_gameStateManager->setGameState(GameState::Menu);

	_decorManager->createBackground("background");
	_decorManager->createStand("stand");
	
	_playerManager->createPlayer();
	_timerManager->createGameTimer();
}

GameManager& GameManager::getInstance()
{
	static GameManager g;
	return g;
}

void GameManager::update(float dt)
{
	_manager.refresh();
	_manager.update(dt);
	_colliderManager->update(dt);
	_effectManager->update(dt);
}

void GameManager::draw()
{
	_decorManager->draw();
	_bulletManager->draw();
	_targetManager->draw();
	_playerManager->draw();
	_effectManager->draw();
	_uiManager->draw();
}

const AssetsManagerPtr& GameManager::getAssetsManager()
{
	return _assetsManager;
}

const InputManagerPtr& GameManager::getInputManager()
{
	return _inputManager;
}

const PlayerManagerPtr& GameManager::getPlayerManager()
{
	return _playerManager;
}

const DecorManagerPtr& GameManager::getDecorManager()
{
	return _decorManager;
}

const GameStateManagerPtr& GameManager::getGameStateManager()
{
	return _gameStateManager;
}

const UIManagerPtr& GameManager::getUIManager()
{
	return _uiManager;
}

const TimerManagerPtr& GameManager::getTimerManager()
{
	return _timerManager;
}

const BulletManagerPtr& GameManager::getBulletManager()
{
	return _bulletManager;
}

const ColliderManagerPtr& GameManager::getColliderManager()
{
	return _colliderManager;
}

const TargetManagerPtr& GameManager::getTargetManager()
{
	return _targetManager;
}

const GameScoreManagerPtr& GameManager::getGameScoreManager()
{
	return _gameScoreManager;
}

const EffectManagerPtr& GameManager::getEffectManager()
{
	return _effectManager;
}
