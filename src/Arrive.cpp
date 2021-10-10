#include "Arrive.h"

Arrive::Arrive()
{
}

Arrive::~Arrive()
{
}

Vector2D Arrive::calculateSteeringForce(Agent* agent, float dtime)
{
	Vector2D desiredVelocity = agent->getTarget() - agent->getPosition();
	float dist = desiredVelocity.Length();
	desiredVelocity.Normalize();

	float factor = dist / agent->getSlowingRadius();

	if (dist > agent->getSlowingRadius())
	{
		desiredVelocity *= agent->getMaxVelocity();
	}
	else
	{
		desiredVelocity *= (agent->getMaxVelocity() * factor);
	}

	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce.Normalize();
	return steeringForce * agent->getMaxForce();
}
