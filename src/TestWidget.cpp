#include "stdafx.h"
#include "TestWidget.h"
#include "GameManager.h"

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
{
	Init();
}

void TestWidget::Init()
{
	GameI.init();
}

void TestWidget::Draw()
{
	GameI.draw();
}

void TestWidget::Update(float dt)
{
	GameI.update(dt);
}

bool TestWidget::MouseDown(const IPoint &mouse_pos)
{
	InputManagerI->setInput(InputType::MouseButtonDown, mouse_pos);
	return false;
}

void TestWidget::MouseMove(const IPoint &mouse_pos)
{
	InputManagerI->setInput(InputType::MouseMove, mouse_pos);
}

void TestWidget::MouseUp(const IPoint &mouse_pos)
{
	InputManagerI->setInput(InputType::MouseButtonUp, mouse_pos);
}