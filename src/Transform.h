#pragma once
#include <Utils/Vector3.h>
#include "ECS.h"

class Transform : public Component
{
public:
	void init() override;
	
	const FPoint& getPosition();
	
	void setPosition(const FPoint& position);
	void setPosition(float x, float y);
	
	void setAnchor(float x, float y);
	const FPoint& getAnchor();
	
	float getRotation();
	void setRotation(float angle);

	float getScale() const;
	void setScale(float scale);

	void setRect(const IRect& rect);
	const FRect& getRect();

	void update(float dt){};

 
private:
	float _scale;
	float _angle;
	FPoint _position;
	FPoint _anchor;
 
	FRect _rect;
};