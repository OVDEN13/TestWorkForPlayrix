#pragma once
class Manager;
class EffectsContainer;

class EffectManager
{
public:
	EffectManager(Manager* manager);
	void changedState();
	void update(float dt);
	void draw();
	ParticleEffectPtr addEffect(std::string effectName, const FPoint& point = FPoint());
private:
	EffectsContainer _effectsContainer;
	Manager* _manager;
};

typedef std::shared_ptr<EffectManager> EffectManagerPtr;