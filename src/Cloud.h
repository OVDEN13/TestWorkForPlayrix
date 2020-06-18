#pragma once

#include "Node.h"
#include "Transform.h"

class Cloud : public Component
{
public:
	void init() override;
	void setPositions(FPoint position, FPoint endPosition, float time);
	void update(float dt) override;
private:
	Transform* _transform;
	Node* _node;
	
	FPoint _startPos;
	FPoint _endPos;
	
	FPoint _speed;
};