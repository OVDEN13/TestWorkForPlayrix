#include "stdafx.h"
#include "EffectManager.h"

#include <Particles\EffectsContainer.h>
#include "GameManager.h"
#include "ECS.h"

EffectManager::EffectManager(Manager* manager) : _manager(manager)
{
}

void EffectManager::changedState()
{
	switch (GameStateManagerI->getGameState())
	{
		case GameState::Pause:
			_effectsContainer.Pause();
			break;
		case GameState::Playing:
			_effectsContainer.Continue();
			break;
		case GameState::Finish:
			_effectsContainer.KillAllEffects();
			break;
	}
}

void EffectManager::update(float dt)
{
	_effectsContainer.Update(dt);
}

void EffectManager::draw()
{
	_effectsContainer.Draw();
}

ParticleEffectPtr EffectManager::addEffect(std::string effectName, const FPoint& point)
{
	return _effectsContainer.AddEffect(effectName, point);
}
