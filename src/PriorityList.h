#pragma once
#include "Agent.h"
#include <list>

class PriorityList :
	public Agent::SteeringBehavior
{
	std::list<Agent::SteeringBehavior*> mySteeringsBehaviors;
	
public:
	PriorityList();
	PriorityList(std::list<Agent::SteeringBehavior*> _sb);
	~PriorityList();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
};