#include "Flee.h"

Flee::Flee()
{
}

Flee::~Flee()
{
}

Vector2D Flee::calculateSteeringForce(Agent *agent, float dtime)
{
	Vector2D desiredVelocity = agent->getPosition() - agent->getTarget();
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce.Normalize();
	return steeringForce * agent->getMaxForce();
}
