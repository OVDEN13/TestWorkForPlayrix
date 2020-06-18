#pragma once
#include "ECS.h"
#include "Collider.h"

class Node;
class Timer;
class Effect;
class Transform;
class Collider;

class Target : public Component
{
public:
	void init() override;
	void update(float dt) override;
	
	virtual void collision(Entity* other);
	
	void setDelay(double time);
	void setSpawnPosition(const FPoint& startPosition, float maxSpeed);
	void setTexture(const std::string texture);

private:
	void initCollider();
	void spawn();
	void collidedWithBullet();
protected:
	FPoint _speed;
	std::string _texture;
	bool _isCreated;
	
	//Components 
	Collider* _collider;
	Transform* _transform;
	Node* _node;
	Timer* _timer;
	Effect* _effect;
	bool _destroyed;
};