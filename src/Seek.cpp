#include "Seek.h"

Seek::Seek()
{
}

Seek::~Seek()
{
}

Vector2D Seek::calculateSteeringForce(Agent *agent, float dtime)
{
	Vector2D desiredVelocity = agent->getTarget() - agent->getPosition();
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce.Normalize();
	return steeringForce * agent->getMaxForce();

}
