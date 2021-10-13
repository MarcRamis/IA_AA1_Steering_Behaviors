#pragma once
#include "Agent.h"

class WeightedBlending :public Agent::SteeringBehavior
{
	std::vector<Agent> agents;

public:
	WeightedBlending();
	~WeightedBlending();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
};