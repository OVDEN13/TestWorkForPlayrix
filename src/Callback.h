#pragma once
#include <functional>
#include <string>
#include "ECS.h"

typedef std::function<void()> CallbackVoid;
typedef std::function<void(int)> CallbackInt;
typedef std::function<void(const std::string&)> CallbackString;
typedef std::function<void(Entity*)> CallbackEntity;