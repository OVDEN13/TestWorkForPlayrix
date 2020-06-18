#include "stdafx.h"

#include "GameManager.h"
#include "Node.h"
#include "Transform.h"

void Node::init()
{
	_texture = nullptr;
	_UV = FRect(0, 1, 0, 1);
	
	if (!entity->hasComponent<Transform>())
	{
		entity->addComponent<Transform>();
	} 
	_transform = &entity->getComponent<Transform>();
}

void Node::draw()
{
	if(!_texture)
	{
		return;
	}
	Render::device.PushMatrix();
	const auto& position = _transform->getPosition();
	Render::device.MatrixTranslate(position);
	Render::device.MatrixScale(_transform->getScale());
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _transform->getRotation());

	const FPoint& anchor = _transform->getAnchor();
	const FRect& rect = _transform->getRect();
	
	auto offset = FPoint(-rect.Width() * anchor.x, -rect.Height() * anchor.y);
	Render::device.MatrixTranslate(offset);
	
	_texture->Bind();
	Render::DrawQuad(rect, _UV);
	Render::device.PopMatrix();
}

void Node::setTexture(std::string textureId)
{
	_texture = AssetsManagerI->getTexture(textureId);
	if(!_texture)
	{
		return;
	}
	_transform->setRect(_texture->getBitmapRect());
}

Render::Texture* Node::getTexture()
{
	return _texture;
}