#pragma once
#include "Agent.h"

class Separation : 
	public Agent::SteeringBehavior
{
public:
	
	Separation();
	~Separation();
	//Vector2D calculateSteeringForce(std::vector<Agent>* agents, float dtime);
};