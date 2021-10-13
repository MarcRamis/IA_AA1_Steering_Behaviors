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

Vector2D Seek::calculateSteeringForce(std::vector<Agent::SteeringBehavior*> steeringBehaviours, std::vector<float> weight, float dtime)
{
	return Vector2D();
}
