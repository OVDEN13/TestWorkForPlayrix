#pragma once
#include "stdafx.h"

class Manager;

enum class InputType
{
	MouseButtonDown,
	MouseButtonUp,
	MouseMove
};

class InputManager
{
public:
	InputManager(Manager* man);
	void setInput(InputType type, const IPoint& mousePos);
private:
	Manager* _manager;
};

typedef std::shared_ptr<InputManager> InputManagerPtr;