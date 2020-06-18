#pragma once

#include "Input.h"
#include "Node.h"
#include "Timer.h"
#include "Transform.h"

class Cannon : public Input
{
public:
	void init() override;
	void setCooldown(double time);
private:
	virtual void mouseButtonDown(const IPoint& mousePos);
	virtual void mouseMove(const IPoint& mousePos);
private:
	double _cooldown;
	Timer* _timer;
	Transform* _transform;
	Node* _node;
	bool _canShoot;
};