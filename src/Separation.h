#pragma once
#include "Agent.h"

class Separation : public Agent::SteeringBehavior
{
public:
	
	Separation();
	Separation(Agent agent);
	~Separation();
};

