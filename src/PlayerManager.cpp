#include "stdafx.h"
#include "PlayerManager.h"
#include "Aim.h"
#include "Cannon.h"
#include "Node.h"
#include "Transform.h"
#include "ECS.h"

const double COOLDOWN = 0.5;

PlayerManager::PlayerManager(Manager* manager) : _manager(manager)
{
}

void PlayerManager::draw()
{
	for (const auto e : _manager->getGroup(PLAYER))
	{
		e->draw();
	}
}

void PlayerManager::createPlayer()
{
	createGun();
	auto& player = _manager->addEntity();
	player.addComponent<Aim>();
}

void PlayerManager::createGun()
{
	auto& gun = _manager->addEntity();
	auto& cannon = gun.addComponent<Cannon>();
	cannon.setCooldown(COOLDOWN);
}
