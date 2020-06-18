#include "stdafx.h"
#include "Target.h"
#include "GameManager.h"
#include "GameScore.h"
#include "Collider.h"
#include "Effect.h"
#include "Transform.h"
#include "Node.h"
#include "Timer.h"

void Target::init()
{
	_isCreated = false;
	_speed = FPoint();
	_texture = "";
	_destroyed = false;
	if (!entity->hasComponent<Transform>())
	{
		entity->addComponent<Transform>();
	}
	_transform = &entity->getComponent<Transform>();
	_transform->setScale(0.35);

	if (!entity->hasComponent<Node>())
	{
		entity->addComponent<Node>();
	}
	_node = &entity->getComponent<Node>();

	if (!entity->hasComponent<Collider>())
	{
		entity->addComponent<Collider>();
	}
	_collider = &entity->getComponent<Collider>();

	if (!entity->hasComponent<Timer>())
	{
		entity->addComponent<Timer>();
	}
	_timer = &entity->getComponent<Timer>();

	if (!entity->hasComponent<Effect>())
	{
		entity->addComponent<Effect>();
	}
	_effect = &entity->getComponent<Effect>();
	
}

void Target::update(float dt)
{
	if (GameStateManagerI->getGameState() == GameState::Playing && _isCreated)
	{
		_transform->setPosition(_transform->getPosition() + (_speed * dt));
		
	}
	// ”ничтожаем обьект только после анимации
	if(_destroyed && _effect->getEffect() && _effect->isFinished())
	{
		entity->destroy();
	}
}

void Target::collision(Entity* other)
{
	switch (other->getComponent<Collider>().getTag())
	{
		case TAG::BULLETS:
			collidedWithBullet();
			break;
		case TAG::TARGETS:
		case TAG::WALLS:
			_speed = FPoint(-_speed.x, _speed.y);
			break;
	}
}

void Target::setSpawnPosition(const FPoint& startPosition, float maxSpeed)
{
	_transform->setPosition(startPosition);
	
	float speed = math::random(maxSpeed / 2.0f, maxSpeed);
	float x = math::random(-1.0f, 1.0f);
	float y = -1  * (maxSpeed / speed);
	
	_speed = FPoint(x, y) * 50;
}

void Target::setTexture(const std::string texture)
{
	_texture = texture;
}

void Target::setDelay(double time)
{
	_timer->setInitTime(time,true);
	_timer->setCallback([=]()
	{
			spawn();
	});
	_timer->play();
}

void Target::spawn()
{
	_node->setTexture(_texture);
	initCollider();
	_isCreated = true;
}

void Target::initCollider()
{
	_collider->setTag(TAG::TARGETS);
	_collider->setType(COLLIDER_TYPE::CIRCLE);
	_collider->setRadius((_transform->getRect().Width() / 2.0f) * _transform->getScale() - 10.0f);
	_collider->setCallback([=](Entity* other)
		{
			collision(other);
		});
	entity->addGroup(COLLIDERS);
}

void Target::collidedWithBullet()
{
	if(!_destroyed)
	{
		_destroyed = true;
		_node->setTexture("");
		_collider->setTag(TAG::NONE);
		MM::manager.StopAll();
		MM::manager.PlaySample("sfx_explosion");
		_effect->setEffect(EffectManagerI->addEffect("FindItem", _transform->getPosition()));
		GameScoreManagerI->getGameScore().getComponent<GameScore>().addScore(50);
	}
}