#pragma once
#include "Agent.h"
#include "Wall.h"

#include <vector>

using namespace Vector2DUtils;

class ObstacleAvoidance :
	public Agent::SteeringBehavior
{
private:
	std::vector<Wall*> walls;

public:
	ObstacleAvoidance();
	~ObstacleAvoidance();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
};