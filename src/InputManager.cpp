#include "stdafx.h"
#include "InputManager.h"
#include "Aim.h"
#include "Button.h"
#include "Cannon.h"
#include "ECS.h"
#include "GameManager.h"

InputManager::InputManager(Manager *man) : _manager(man) {}

void InputManager::setInput(InputType type, const IPoint &mousePos) {
    if (GameStateManagerI->getGameState() == GameState::Playing) {
        for (const auto e : _manager->getGroup(GROUP_NAME::PLAYER)) {
            if (e->hasComponent<Aim>()) {
                e->getComponent<Aim>().setInput(type, mousePos);
            }
            if (e->hasComponent<Cannon>()) {
                e->getComponent<Cannon>().setInput(type, mousePos);
            }
        }
    }
    for (const auto e : _manager->getGroup(GROUP_NAME::BUTTONS)) {
        if (e->hasComponent<Button>()) {
            e->getComponent<Button>().setInput(type, mousePos);
        }
    }
}
