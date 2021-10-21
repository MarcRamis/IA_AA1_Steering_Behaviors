#include "Cohesion.h"

Cohesion::Cohesion()
{
}

Cohesion::~Cohesion()
{
}

Vector2D Cohesion::calculateSteeringForce(Agent* agent, float dtime)
{
	Vector2D averagePos = Vector2D(0.f, 0.f);

	if (agent->getNeighbour_flock().size() != 0) {
		for (Agent* agent_in_neighbourFlock : agent->getNeighbour_flock()) {

			averagePos += agent_in_neighbourFlock->getPosition();
		}
		averagePos /= agent->getNeighbour_flock().size();
		averagePos -= agent->getPosition();
	}
	averagePos.Normalize();
	averagePos *= agent->getMaxVelocity();
	Vector2D steeringForce = averagePos - agent->getVelocity();
	steeringForce.Normalize();
	return steeringForce * agent->getMaxForce();
}
