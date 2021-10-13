#pragma once
#include "Agent.h"

class Arrive :
    public Agent::SteeringBehavior
{
public:
    Arrive();
    ~Arrive();
    Vector2D calculateSteeringForce(Agent* agent, float dtime);
    Vector2D calculateSteeringForce(std::vector<Agent::SteeringBehavior*> steeringBehaviours, std::vector<float> weight, float dtime);
};