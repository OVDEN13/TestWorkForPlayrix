#include "stdafx.h"
#include "Transform.h"

void Transform::init()
{
	_scale = 1.0f;
	_angle = 0.0f;
	_position = FPoint();
	_anchor= FPoint(0.5f, 0.5f);
	_rect = FRect();
}

const FPoint& Transform::getPosition()
{
	return _position;
}

void Transform::setPosition(const FPoint& position)
{
	_position = position;
}

void Transform::setPosition(float x, float y)
{
	setPosition(FPoint (x, y));
}

void Transform::setAnchor(float x, float y)
{
	_anchor = FPoint(x, y);
}

const FPoint& Transform::getAnchor()
{
	return _anchor;
}

float Transform::getRotation()
{
	return _angle;
}

void Transform::setRotation(float angle)
{
	_angle = angle;
	
}

float Transform::getScale() const
{
	return _scale;
}

void Transform::setScale(float scale)
{
	_scale = scale;
}
 
void Transform::setRect(const IRect& rect)
{
	_rect = FRect(rect);
}

const FRect& Transform::getRect()
{
	return _rect;
}