#pragma once
#include <memory>
#include "Entity.h"

class EntityFactory
{
public:
	static std::unique_ptr<Entity>createPlayer(float);
};