#pragma once
#include "Input.h"
#include "Node.h"
#include "Transform.h"

class Aim : public Input
{
public:
	void init() override;
private:
	virtual void mouseMove(const IPoint& mousePos);
private:
	Transform* _transform;
	Node* _node;
};