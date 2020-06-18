#pragma once
#include "ECS.h"
#include "Effect.h"

class Collider;
class Transform;
class Node;

class Bullet : public Component
{
public:
	void init() override;
	void update(float dt) override;
	void setTarget(const IPoint& mousePos, float speed, bool isPunchy = false);
	void collision(Entity* other);
private:
	void initCollider();
	void hitTarget();
private:
	FPoint _dir;
	FPoint _speed;
	bool _isPunchy;

	Collider* _collider;
	Transform* _transform;
	Node* _node;
	Effect* _effect;
};