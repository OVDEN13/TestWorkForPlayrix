#include "stdafx.h"
#include "Collider.h"


void Collider::init() {
	_tag = TAG::NONE;
	_type = COLLIDER_TYPE::BOX;

	_collider = FRect();
	_needAutoUpdate = false;

	if (!entity->hasComponent<Transform>()) {
		entity->addComponent<Transform>();
	}
	_transform = &entity->getComponent<Transform>();
}

void Collider::update(float dt) {
	// Обновляем позицию коллайдера только тогда, когда это требуется
	if (_needAutoUpdate && _currentPosition != _transform->getPosition()) {
		recalculateCollider();
	}
}

const TAG &Collider::getTag()
{
	return _tag;
}

void Collider::setTag(const TAG &tag)
{
	_tag = tag;
}

const COLLIDER_TYPE &Collider::getType()
{
	return _type;
}

void Collider::setType(const COLLIDER_TYPE &type)
{
	_type = type;
}

void Collider::setRadius(float radius)
{
	_radius = radius;
}

float Collider::getRadius()
{
	return _radius;
}

const FRect &Collider::getCollider()
{
	return _collider;
}

void Collider::setCollider(const FRect &rect)
{
	_collider = rect;
}

void Collider::needAutoUpdate(bool enable)
{
	_needAutoUpdate = enable;
}

void Collider::recalculateCollider() {
	const FPoint& position = _transform->getPosition();
	const FRect& textrureRect = _transform->getRect();
	const FPoint& anchor = _transform->getAnchor();
	float scale = _transform->getScale();

	auto xOffset = (textrureRect.Width() * scale) * anchor.x;
	auto yOffset = (textrureRect.Height() * scale) * anchor.y;
	_collider = FRect(position.x - xOffset,
		position.x + (textrureRect.Width() * scale) - xOffset,
		position.y - yOffset,
		position.y + (textrureRect.Height() * scale) - yOffset);
}

void Collider::setCallback(CallbackEntity callback)
{
	_callback = callback;
}

void Collider::onCollision(Entity *entity) {
	if (_callback) {
		_callback(entity);
	}
}
