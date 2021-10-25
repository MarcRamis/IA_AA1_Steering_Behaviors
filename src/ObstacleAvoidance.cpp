#include "ObstacleAvoidance.h"


ObstacleAvoidance::ObstacleAvoidance()
{
}

ObstacleAvoidance::~ObstacleAvoidance()
{
}

Vector2D ObstacleAvoidance::calculateSteeringForce(Agent* agent, float dtime)
{
	Vector2D velocityNorm = Vector2D(agent->getVelocity().x / agent->getVelocity().Length(), agent->getVelocity().y / agent->getVelocity().Length());
	Vector2D raycastVector = agent->getPosition() + velocityNorm * K_RAYCAST_LENGTH;

	Vector2D intersectionPoint, normalVector;
	bool obstacleAvoidanceCollision = false;

	for (Wall *w : walls)
	{
	}

	return Vector2D(0.f, 0.f);
}

void ObstacleAvoidance::setWalls(Wall *wall)
{
	walls.push_back(wall);
}
