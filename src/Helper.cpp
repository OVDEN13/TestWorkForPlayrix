#include "stdafx.h"
#include "Helper.h"

float Helper::lookAtTarget(const FPoint& position, const FPoint& target)
{
	auto offset = target - position;
	offset = offset.Normalized();
    return atan2f(offset.x, offset.y) * RAD2DEG;;
}

 