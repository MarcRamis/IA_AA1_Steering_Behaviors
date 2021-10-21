#include "Separation.h"

Separation::Separation() {}
Separation::~Separation() {}

Vector2D Separation::calculateSteeringForce(Agent* agent, float dtime)
{
	Vector2D separationVector = Vector2D(0.f,0.f);
	
	if (agent->getNeighbour_flock().size() != 0) {
		for (Agent* agent_in_neighbourFlock : agent->getNeighbour_flock()) {

			separationVector += (agent->getPosition() - agent_in_neighbourFlock->getPosition());
		}
		separationVector /= agent->getNeighbour_flock().size();
	}
	separationVector.Normalize();
	separationVector *= agent->getMaxVelocity();
	Vector2D steeringForce = separationVector - agent->getVelocity();
	steeringForce.Normalize();
	return steeringForce * agent->getMaxForce();
}