#include "stdafx.h"
#include "Button.h"

void Button::init()
{
	if (!entity->hasComponent<Transform>())
	{
		entity->addComponent<Transform>();
	}
	_transform = &entity->getComponent<Transform>();
	
	if (!entity->hasComponent<Node>())
	{
		entity->addComponent<Node>();
	}
	_node = &entity->getComponent<Node>();

	if (!entity->hasComponent<Collider>())
	{
		entity->addComponent<Collider>();
	}
	_collider = &entity->getComponent<Collider>();
	
	_collider->setTag(TAG::BUTTONS);
	_collider->setType(COLLIDER_TYPE::BOX);

	_callback = nullptr;
	_isSelected = false;
	
	entity->addGroup(GROUP_NAME::BUTTONS);
	entity->addGroup(GROUP_NAME::UI);
}

void Button::update(float dt)
{
}

void Button::setCallback(CallbackEntity callback)
{
	_callback = callback;
}

void Button::setButtonImages(ButtonImages buttonImages)
{
	_buttonImages = buttonImages;
	_node->setTexture(_buttonImages.normalImage);
	_collider->recalculateCollider();
}

void Button::mouseButtonDown(const IPoint& mousePos)
{

}

void Button::mouseButtonUp(const IPoint& mousePos)
{
	if (_isSelected && _callback)
	{
		_callback(entity);
	}
}

void Button::mouseMove(const IPoint& mousePos)
{
	changeButtonImage(_collider->getCollider().Contains(mousePos));
}

void Button::changeButtonImage(bool isSelected)
{
	if(_isSelected != isSelected)
	{
		_node->setTexture(isSelected ? _buttonImages.highlightedImage : _buttonImages.normalImage);
		_isSelected = isSelected;
	}
}