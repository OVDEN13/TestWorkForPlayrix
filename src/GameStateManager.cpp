#include "stdafx.h"
#include "GameStateManager.h"
#include "GameManager.h"

GameStateManager::GameStateManager()  : _gameState(GameState::Menu)
{
	
}

void GameStateManager::setGameState(const GameState& gameState)
{
	_gameState = gameState;
	GameI.changedState();
}

const GameState& GameStateManager::getGameState()
{
	return _gameState;
}
