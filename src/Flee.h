#pragma once
#include "Agent.h"

class Flee :
	public Agent::SteeringBehavior
{
public:
	Flee();
	~Flee();
	Vector2D calculateSteeringForce(Agent *agent, float dtime);
};
