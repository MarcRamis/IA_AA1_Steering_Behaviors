#pragma once
#include "Agent.h"

class Separation : 
	public Agent::SteeringBehavior
{
public:
	
	Separation();
	~Separation();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
};