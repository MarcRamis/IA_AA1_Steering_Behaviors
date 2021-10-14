#pragma once
#include "Agent.h"

class WeightedBlending :public Agent::SteeringBehavior
{
	std::vector<Agent::SteeringBehavior*> m_SB;
	std::vector<float*> m_Weight;

public:
	WeightedBlending();
	WeightedBlending(std::vector<Agent::SteeringBehavior*> _sb, std::vector<float*> _weight);
	~WeightedBlending();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
	Vector2D calculateSteeringForce(std::vector<Agent::SteeringBehavior*> steeringBehaviours, std::vector<float> weight, float dtime);
	Vector2D combinateSteeringForces();
};