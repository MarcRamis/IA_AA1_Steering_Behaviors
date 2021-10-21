#pragma once
#include "Agent.h"
#include <vector>


class PriorityList :
	public Agent::SteeringBehavior
{
	std::vector< Agent::SteeringBehavior*> mySteeringsBehaviors;
	std::vector<float*> steeringPriority_K;
	

public:
	PriorityList();
	PriorityList(std::vector<Agent::SteeringBehavior*> _sb, std::vector<float*> _steeringPriority_K);
	~PriorityList();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
};