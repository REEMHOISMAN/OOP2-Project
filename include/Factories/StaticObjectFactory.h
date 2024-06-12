#pragma once 
#include <memory>
#include <Obstacle.h>

class StaticObjectFactory
{
public:
	static std::unique_ptr<Obstacle>createObstacle(float, float, const std::string);
};