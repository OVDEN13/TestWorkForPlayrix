#pragma once
#include "ECS.h"

class Transform;

class Node : public Component
{
public:
	void init() override;
	void draw() override;
	
	void setTexture(std::string textureId);
	Render::Texture* getTexture();
private:
	Transform* _transform;
	Render::Texture* _texture;
	FRect _UV;
};