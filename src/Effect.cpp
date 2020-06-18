#include "stdafx.h"
#include "Effect.h"
#include "Transform.h"

Effect::~Effect() {
    if (_effect) {
        _effect->Kill();
    }
}

void Effect::init() {
    if (!entity->hasComponent<Transform>()) {
        entity->addComponent<Transform>();
    }
    _transform = &entity->getComponent<Transform>();
    _effect = nullptr;
    entity->addGroup(GROUP_NAME::EFFECTS);
}

void Effect::setEffect(const ParticleEffectPtr &effect) {
    _effect = effect;
    _effect->SetPos(_transform->getPosition());
}

const ParticleEffectPtr &Effect::getEffect()
{
    return _effect;
}

void Effect::setScale(float scale)
{
	_effect->SetScale(scale, scale);
}

void Effect::pause()
{
	_effect->Pause();
}

void Effect::play()
{
	_effect->Continue();
}

bool Effect::isFinished()
{
	return _effect->ended;
}

void Effect::kill()
{
	_effect->Kill();
}

void Effect::setPosition(const FPoint &point)
{
	_effect->SetPos(point);
}
