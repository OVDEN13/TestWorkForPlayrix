#pragma once
#include "ECS.h"

class Transform;

class Effect : public Component
{
public:
	~Effect();
	void init() override;

	void setEffect(const ParticleEffectPtr& effect);
	const ParticleEffectPtr& getEffect();
	void setScale(float scale);
	void pause();
	void play();
	bool isFinished();
	void kill();
	void setPosition(const FPoint& point);
private:
	Transform* _transform;
	ParticleEffectPtr _effect;
};