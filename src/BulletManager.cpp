#include "stdafx.h"
#include "BulletManager.h"
#include "GameManager.h";
#include "Node.h"
#include "Transform.h"
#include "Bullet.h"
#include "LifeTimer.h"
#include "ECS.h"

CONST double LIFE_TIME = 5.0;

BulletManager::BulletManager(Manager* manager) :_manager(manager) , _bulletSpeed(50.0f)
{
	_bulletSpeed = AssetsManagerI->getStaticGameConfig().bulletSpeed;
}

void BulletManager::changedState()
{
	switch (GameStateManagerI->getGameState())
	{
		case GameState::Finish:
			for (const auto e : _manager->getGroup(BULLETS))
			{
				e->destroy();
			}
			break;
	}
}

void BulletManager::createBullet(bool isPunchy)
{
	auto& gameObject = _manager->addEntity();
	auto& transform = gameObject.addComponent<Transform>();
	auto& node = gameObject.addComponent<Node>();
	node.setTexture("cannonball");
	//Spawn pos
	transform.setPosition(calculateSpawnPosition());
	transform.setAnchor(0.5f, 0.5f);
	transform.setScale(0.25f);
	gameObject.addComponent<Effect>();
 
	auto& bullet = gameObject.addComponent<Bullet>();
	auto& lifeTimer = gameObject.addComponent<LifeTimer>();

	lifeTimer.setDelay(LIFE_TIME);
	bullet.setTarget(Core::mainInput.GetMousePos(), _bulletSpeed, isPunchy);
}

void BulletManager::draw()
{
	for (const auto e : _manager->getGroup(BULLETS))
	{
		if (e->hasComponent<Node>())
		{
			e->getComponent<Node>().draw();
		}
	}
}

FPoint BulletManager::calculateSpawnPosition()
{
	auto mousePos(FPoint(Core::mainInput.GetMousePos()));
	auto playerPos = FPoint(Render::device.Width() / 2.0f, 35.0f);

	auto dir = mousePos - playerPos;
	dir.Normalize();
	// Длина пушки
	float gunLength = 155;
	return playerPos + (dir* gunLength);
}
