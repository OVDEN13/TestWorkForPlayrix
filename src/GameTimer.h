#pragma once

#include "ECS.h"
#include "TextNode.h"
#include "Timer.h"

class GameTimer : public Component
{
public:
	void init() override;
	void update(float dt) override;
private:
	TextNode* _textNode;
	Timer* _timer;
};