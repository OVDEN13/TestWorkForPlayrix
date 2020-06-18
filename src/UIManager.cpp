#include "stdafx.h"
#include "GameManager.h"
#include "UIManager.h"
#include "Button.h"
#include "GameScore.h"
#include "TextNode.h"
#include "Transform.h"
#include "ECS.h"

UIManager::UIManager(Manager* manager) : _manager(manager)
{
}

void UIManager::changedState()
{
	clear();
	switch (GameStateManagerI->getGameState())
	{
		case GameState::Menu:
			showPlayButton();
			break;
		case GameState::Playing:
			showGameUI();
			break;
		case GameState::Pause:
			showPauseUI();
			break;
		case GameState::Finish:
			showFinishUI();
			break;
	}
}

void UIManager::showPlayButton()
{
	auto& playBtn = createButton();
	auto& transform = playBtn.getComponent<Transform>();

	transform.setPosition(Render::device.Width() / 2, Render::device.Height() / 2);
	transform.setAnchor(0.5f, 0.5f);

	auto& button = playBtn.getComponent<Button>();

	ButtonImages images;
	images.highlightedImage = "ButtonsStyle9_03";
	images.normalImage = "ButtonsStyle11_03";
	CallbackEntity callback = [](Entity* entity)
	{
		GameStateManagerI->setGameState(GameState::Playing);
	};

	button.setButtonImages(images);
	button.setCallback(callback);
}

void UIManager::showGameUI()
{
	auto& pauseBtn = createButton();
	auto& transform = pauseBtn.getComponent<Transform>();
	transform.setScale(0.30f);
	transform.setPosition(50, Render::device.Height() - 50);
	transform.setAnchor(0.5f, 0.5f);
	
	auto& button = pauseBtn.getComponent<Button>();
	
	CallbackEntity callback = [](Entity* entity)
	{
		GameStateManagerI->setGameState(GameState::Pause);
	};

	ButtonImages images;
	images.highlightedImage = "ButtonsStyle9_02";
	images.normalImage = "ButtonsStyle11_02";

	button.setButtonImages(images);
	button.setCallback(callback);
}

void UIManager::showPauseUI()
{
	auto center = FPoint(Render::device.Width() / 2, Render::device.Height() / 2);
	{
		auto& resume = createButton();
		auto& transform = resume.getComponent<Transform>();
		 
		transform.setScale(0.50f);
		transform.setPosition(center.x * 0.5f,center.y);
		transform.setAnchor(0.5f, 0.5f);

		auto& button = resume.getComponent<Button>();

		CallbackEntity callback = [](Entity* entity)
		{
			GameStateManagerI->setGameState(GameState::Playing);
		};
		
		ButtonImages images;
		images.highlightedImage = "ButtonsStyle9_03";
		images.normalImage = "ButtonsStyle11_03";
		
		button.setButtonImages(images);
		button.setCallback(callback);
	}
	{
		auto& resume = createButton();
		auto& transform = resume.getComponent<Transform>();

		transform.setScale(0.50f);
		transform.setPosition(center.x * 1.5f, center.y);
		transform.setAnchor(0.5f, 0.5f);

		auto& button = resume.getComponent<Button>();

		CallbackEntity callback = [](Entity* entity)
		{
			GameStateManagerI->setGameState(GameState::Finish);
		};

		ButtonImages images;
		images.highlightedImage = "ButtonsStyle9_04";
		images.normalImage = "ButtonsStyle11_04";
		
		button.setButtonImages(images);
		button.setCallback(callback);
	}
	
}

void UIManager::showFinishUI()
{
	auto center = FPoint(Render::device.Width() / 2, Render::device.Height() / 2);
	
	ButtonImages images;
	images.highlightedImage = "ButtonsStyle9_04";
	images.normalImage = "ButtonsStyle11_04";

	auto& resume = createButton();
	auto& transform = resume.getComponent<Transform>();

	transform.setScale(0.50f);
	transform.setPosition(center);
	transform.setAnchor(0.5f, 0.5f);

	auto& button = resume.getComponent<Button>();

	CallbackEntity callback = [](Entity* entity)
	{
		GameStateManagerI->setGameState(GameState::Menu);
	};

	button.setButtonImages(images);
	button.setCallback(callback);
	auto& collider = resume.getComponent<Collider>();
	collider.recalculateCollider();

	auto& score = _manager->addEntity();
	auto& textNode = score.addComponent<TextNode>();
	auto& scoreTransform = score.getComponent<Transform>();
	scoreTransform.setPosition(center.x, center.y + 150.0f);
	scoreTransform.setScale(2);
	textNode.setText("SCORE : " + std::to_string(GameScoreManagerI->getGameScore().getComponent<GameScore>().getScore()));
	
}

void UIManager::clear()
{
	for (const auto e : _manager->getGroup(GROUP_NAME::BUTTONS))
	{
		e->destroy();
	}
}


void UIManager::draw()
{
	for (const auto e : _manager->getGroup(GROUP_NAME::UI))
	{
		if (e->hasComponent<Node>())
		{
			e->getComponent<Node>().draw();
		}
		if(e->hasComponent<TextNode>())
		{
			e->getComponent<TextNode>().draw();
		}
	}
}

Entity& UIManager::createUIObject()
{
	auto& uiObject = _manager->addEntity();
	uiObject.addComponent<Transform>();
	uiObject.addComponent<Node>();
	return uiObject;
}

const Entity& UIManager::createButton()
{
	auto& btn = createUIObject();
	btn.addComponent<Button>();
	return btn;
}


