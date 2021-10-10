#pragma once
#include "Agent.h"

class Arrive :
    public Agent::SteeringBehavior
{
public:
    Arrive();
    ~Arrive();
    Vector2D calculateSteeringForce(Agent* agent, float dtime);
};