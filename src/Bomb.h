#pragma once
#include "Target.h"

class Bomb : public Target
{
public:
	virtual void collision(Entity* other);
};