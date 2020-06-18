#include "stdafx.h"
#include "Bomb.h"
#include "GameManager.h"
#include "GameScore.h"

void Bomb::collision(Entity* other)
{
	switch (other->getComponent<Collider>().getTag())
	{
		case TAG::BULLETS:
			GameScoreManagerI->getGameScore().getComponent<GameScore>().reduceScore(150);
			MM::manager.StopAll();
			MM::manager.PlaySample("sfx_explosion");
			entity->destroy();
			break;
		case TAG::TARGETS:
		case TAG::WALLS:
			_speed = FPoint(-_speed.x, _speed.y);
			break;
	}
}