#pragma once
#include "ECS.h"
#include "Transform.h"

class TextNode : public Component
{
public:
	void init() override;
	void draw() override;

	void setText(const std::string& text);
	const std::string& getText();
	
private:
	Transform* _transform;
	std::string _text;
};