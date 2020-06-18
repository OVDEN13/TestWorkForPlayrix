#include "stdafx.h"
#include "Input.h"

void Input::setInput(InputType type, const IPoint& mousePos)
{
	switch (type)
	{
	case InputType::MouseButtonUp:
		mouseButtonUp(mousePos);
		break;
	case InputType::MouseButtonDown:
		mouseButtonDown(mousePos);
		break;
	case InputType::MouseMove:
		mouseMove(mousePos);
		break;
	}
}