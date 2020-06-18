#include "stdafx.h"
#include "Cannon.h"
#include "GameManager.h"
#include "Helper.h"

void Cannon::init()
{
	_cooldown = 3.5;
	_canShoot = true;
	
	if (!entity->hasComponent<Transform>())
	{
		entity->addComponent<Transform>();
	}
	_transform = &entity->getComponent<Transform>();
	_transform->setPosition(Render::device.Width() / 2.0f, 35.0f);
	_transform->setAnchor(0.5f, 0.0f);
	_transform->setScale(0.25f);

	if (!entity->hasComponent<Node>())
	{
		entity->addComponent<Node>();
	}
	_node = &entity->getComponent<Node>();
	_node->setTexture("cannon");
	
	if (!entity->hasComponent<Timer>())
	{
		entity->addComponent<Timer>();
	}
	_timer = &entity->getComponent<Timer>();
	_timer->setTime(0.0);
	_timer->setInitTime(_cooldown);

	entity->addGroup(PLAYER);
}

void Cannon::setCooldown(double time)
{
	_cooldown = time;
}

void Cannon::mouseButtonDown(const IPoint& mousePos)
{

	if (Core::mainInput.GetMouseLeftButton() && _timer->getTime() <= 0.0 && _canShoot)
	{
		MM::manager.PlaySample("cannon_shot");
		BulletManagerI->createBullet();
		_timer->setInitTime(_cooldown,true);
		_timer->play();
	} else if(_timer->getTime() <= 0.0 && _canShoot)
	{
		MM::manager.PlaySample("cannon_shot");
		BulletManagerI->createBullet(true);
		_timer->setInitTime(_cooldown * 5, true);
		_timer->play();
	}
}



void Cannon::mouseMove(const IPoint& mousePos)
{
	float angleRadians = Helper::lookAtTarget(_transform->getPosition(), FPoint(mousePos));
	_canShoot = angleRadians > -75.0f && angleRadians < 75.0f;
	angleRadians = math::max(-75.0f, math::min(angleRadians, 75.0f));
	_transform->setRotation(-angleRadians);
}