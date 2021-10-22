#include "CollissionAvoidance.h"

CollissionAvoidance::CollissionAvoidance()
{
}

CollissionAvoidance::~CollissionAvoidance()
{
}

Vector2D CollissionAvoidance::calculateSteeringForce(Agent* agent, float dtime)
{
	Vector2D desiredVelocity = agent->getPosition() - agent->getTarget();
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce.Normalize();
	return steeringForce * agent->getMaxForce();
}