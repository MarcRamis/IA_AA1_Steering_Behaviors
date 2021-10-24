#include "ObstacleAvoidance.h"


ObstacleAvoidance::ObstacleAvoidance()
{
}

ObstacleAvoidance::~ObstacleAvoidance()
{
}

Vector2D ObstacleAvoidance::calculateSteeringForce(Agent* agent, float dtime)
{
	for (Wall *w : walls)
	{
		// Look at the positive wall side
		if (IsInsideCone(
			Vector2D(w->getPosition().x + w->getWeight(), w->getPosition().y + w->getHeight()),agent->getPosition(), 
			agent->getVelocity().Normalize() * 
			K_CONE_LENGTH_AGENTS,K_CONE_HALFANGLE_AGENTS) 
			|| 
			IsInsideCone(
				Vector2D(w->getPosition().x - w->getWeight(), w->getPosition().y - w->getHeight()), agent->getPosition(),
				agent->getVelocity().Normalize() *
				K_CONE_LENGTH_AGENTS, K_CONE_HALFANGLE_AGENTS))
		{
			return Vector2D(0.f,0.f);
		}
	}
}