#include "Alignment.h"

Alignment::Alignment()
{
}

Alignment::~Alignment()
{
}

Vector2D Alignment::calculateSteeringForce(Agent* agent, float dtime)
{
	Vector2D averageVelocity = Vector2D(0.f, 0.f);

	if (agent->getNeighbour_flock().size() != 0) {
		for (Agent* agent_in_neighbourFlock : agent->getNeighbour_flock()) {

			averageVelocity += agent_in_neighbourFlock->getVelocity();
		}
		averageVelocity /= agent->getNeighbour_flock().size();
	}
	averageVelocity.Normalize();
	averageVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = averageVelocity - agent->getVelocity();
	steeringForce.Normalize();
	return steeringForce * agent->getMaxForce();
}
