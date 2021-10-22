#pragma once
#include "Agent.h"

class CollissionAvoidance :
	public Agent::SteeringBehavior
{
public:
	CollissionAvoidance();
	~CollissionAvoidance();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
};