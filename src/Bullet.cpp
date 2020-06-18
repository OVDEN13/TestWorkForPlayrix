#include "stdafx.h"
#include "Bullet.h"
#include "Collider.h"
#include "Effect.h"
#include "GameManager.h"
#include "Node.h"


void Bullet::init() {
    _dir = FPoint();
    _speed = FPoint();
    _isPunchy = false;

    if (!entity->hasComponent<Transform>()) {
        entity->addComponent<Transform>();
    }
    _transform = &entity->getComponent<Transform>();

    if (!entity->hasComponent<Node>()) {
        entity->addComponent<Node>();
    }
    _node = &entity->getComponent<Node>();

    if (!entity->hasComponent<Collider>()) {
        entity->addComponent<Collider>();
    }
    _collider = &entity->getComponent<Collider>();

    if (!entity->hasComponent<Effect>()) {
        entity->addComponent<Effect>();
    }
    _effect = &entity->getComponent<Effect>();

    initCollider();
}

void Bullet::update(float dt) {
    if (GameStateManagerI->getGameState() == GameState::Playing) {
        _transform->setPosition(_transform->getPosition() + (_speed * dt));
        _effect->setPosition(_transform->getPosition());
    }
}

void Bullet::setTarget(const IPoint &mousePos, float speed, bool isPunchy) {
    _isPunchy = isPunchy;
    FPoint dir = FPoint(mousePos) - _transform->getPosition();
    if (dir.y <= 0) {
        dir = -dir;
    }

    dir.Normalize();
    _dir = dir;
    _speed = dir * speed * 10;

    _effect->setEffect(
        EffectManagerI->addEffect("Iskra2", _transform->getPosition()));
    _effect->setScale(2.0f);
}

void Bullet::collision(Entity *other) {
    switch (other->getComponent<Collider>().getTag()) {
    case TAG::TARGETS:
        hitTarget();
        break;
    case TAG::WALLS:
        _speed = FPoint(-_speed.x, _speed.y);
        break;
    default:
        break;
    }
}

void Bullet::initCollider() {
    _collider->setTag(TAG::BULLETS);
    _collider->setType(COLLIDER_TYPE::CIRCLE);
    _collider->setRadius(
        (_transform->getRect().Width() / 2.0f) * _transform->getScale() - 10.0f);
    _collider->setCallback([=](Entity* other) { collision(other); });
    entity->addGroup(BULLETS);
    entity->addGroup(COLLIDERS);
}

void Bullet::hitTarget() {
    if (!_isPunchy) {
        _effect->kill();
        entity->destroy();
    }
}
