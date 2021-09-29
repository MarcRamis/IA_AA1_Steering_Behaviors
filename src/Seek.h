#pragma once
#include "Agent.h"

class Seek :
	public Agent::SteeringBehavior
{
public:
	Seek();
	~Seek();
	Vector2D calculateSteeringForce(Agent *agent, float dtime);
};
