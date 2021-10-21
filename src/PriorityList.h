#pragma once
#include "Agent.h"
#include <forward_list>

class PriorityList :
	public Agent::SteeringBehavior
{
	std::forward_list<Agent::SteeringBehavior*> priorityList;

public:

	std::forward_list<Agent::SteeringBehavior*> MyPriorityList(std::vector<SteeringBehavior*> _steeringBehaviors);
};

