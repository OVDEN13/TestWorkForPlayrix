#pragma once
#include "AssetsManager.h"
#include "InputManager.h"
#include "PlayerManager.h"
#include "DecorManager.h"
#include "GameStateManager.h"
#include "TimerManager.h"
#include "UIManager.h"
#include "BulletManager.h"
#include "ColliderManager.h"
#include "EffectManager.h"
#include "TargetManager.h"
#include "GameScoreManager.h"

class GameManager  
{
public:
	static GameManager& getInstance();


	void init();
	
	void update(float dt);
	void draw();
	
	void changedState();
	
	const AssetsManagerPtr& getAssetsManager();
	const InputManagerPtr& getInputManager();
	const PlayerManagerPtr& getPlayerManager();
	const DecorManagerPtr& getDecorManager();
	const GameStateManagerPtr& getGameStateManager();
	const UIManagerPtr& getUIManager();
	const TimerManagerPtr& getTimerManager();
	const BulletManagerPtr& getBulletManager();
	const ColliderManagerPtr& getColliderManager();
	const TargetManagerPtr& getTargetManager();
	const GameScoreManagerPtr& getGameScoreManager();
	const EffectManagerPtr& getEffectManager();
private:
	void initManager();
	void initResources();
	void initGame();
	
	GameManager();
	GameManager(GameManager const&) = delete;
	GameManager& operator= (GameManager const&) = delete;
	
private:
	Manager _manager;
	
	AssetsManagerPtr _assetsManager;
	InputManagerPtr _inputManager;
	PlayerManagerPtr _playerManager;
	DecorManagerPtr _decorManager;
	GameStateManagerPtr _gameStateManager;
	UIManagerPtr _uiManager;
	TimerManagerPtr _timerManager;
	BulletManagerPtr _bulletManager;
	ColliderManagerPtr _colliderManager;
	TargetManagerPtr _targetManager;
	GameScoreManagerPtr _gameScoreManager;
	EffectManagerPtr _effectManager;
};

#define GameI (GameManager::getInstance())
#define AssetsManagerI (GameI.getAssetsManager())
#define InputManagerI (GameI.getInputManager())
#define PlayerManagerI (GameI.getPlayerManager())
#define DecorManagerI (GameI.getDecorManager())
#define GameStateManagerI (GameI.getGameStateManager())
#define UIManagerI (GameI.getUIManager())
#define TimerManagerI (GameI.getTimerManager())
#define BulletManagerI (GameI.getBulletManager())
#define ColliderManagerI (GameI.getColliderManager())
#define TargetManagerI (GameI.getTargetManager())
#define GameScoreManagerI (GameI.getGameScoreManager())
#define EffectManagerI (GameI.getEffectManager())