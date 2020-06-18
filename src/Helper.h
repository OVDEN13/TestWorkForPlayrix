#pragma once
#include "Transform.h"

const float RAD2DEG = 180 /math::PI;

class Helper
{
public:
	static float lookAtTarget(const FPoint& position, const FPoint& target);
};

 