#pragma once
#include "Callback.h"
#include "Collider.h"
#include "Input.h"
#include "Node.h"
#include "Transform.h"
#include "UIManager.h"

class Button : public Input
{
public:
	void init() override;
	void update(float dt) override;
	void setCallback(CallbackEntity callback);
	void setButtonImages(ButtonImages buttonImages);
private:
	void mouseButtonDown(const IPoint& mousePos) override;
	void mouseButtonUp(const IPoint& mousePos) override;
	void mouseMove(const IPoint& mousePos) override;
	void changeButtonImage(bool isSelected);
private:
	Transform* _transform;
	Node* _node;
	Collider* _collider;
	ButtonImages _buttonImages;
	CallbackEntity _callback;

	bool _isSelected;
};