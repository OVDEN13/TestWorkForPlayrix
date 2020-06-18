#pragma once
enum class GameState
{
	Menu,
	Playing,
	Pause,
	Finish
};

class GameStateManager
{
public:
	GameStateManager();
	void setGameState(const GameState& gameState);
	const GameState& getGameState();
private:
	GameState _gameState;
};

typedef std::shared_ptr<GameStateManager> GameStateManagerPtr;
 