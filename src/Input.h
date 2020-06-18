#pragma once
#include "InputManager.h"
#include "ECS.h"

class Input : public Component
{
public:
	void setInput(InputType type, const IPoint& mousePos);
private:
	virtual void mouseButtonDown(const IPoint& mousePos) {};
	virtual void mouseButtonUp(const IPoint& mousePos) {};
	virtual void mouseMove(const IPoint& mousePos) {};
};