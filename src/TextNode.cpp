#include "stdafx.h"
#include "TextNode.h"

void TextNode::init()
{
	_text = "";
	if (!entity->hasComponent<Transform>())
	{
		entity->addComponent<Transform>();
	}
	_transform = &entity->getComponent<Transform>();
	entity->addGroup(GROUP_NAME::UI);
}

void TextNode::draw()
{
	if(!_text.empty())
	{
		Render::BindFont("arial");
		Render::PrintString(_transform->getPosition(), _text, _transform->getScale(), CenterAlign);
	}
}

void TextNode::setText(const std::string& text)
{
	_text = text;
}

const std::string& TextNode::getText()
{
	return _text;
}