#pragma once
#include "ECS.h"
#include "TextNode.h"

class GameScore : public Component
{
public:
	void init() override;
	void update(float dt) override;
	void resetScore();
	void addScore(int count);
	void reduceScore(int count);
	int getScore();
private:
	int _score;
	TextNode* _textNode;
};