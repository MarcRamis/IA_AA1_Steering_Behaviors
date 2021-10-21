#pragma once
#include "Agent.h"

class Cohesion :
	public Agent::SteeringBehavior
{
public:

	Cohesion();
	~Cohesion();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
};

