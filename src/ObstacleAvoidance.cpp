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
	Vector2D avoidTarget = Vector2D(0.f, 0.f);
	Vector2D desiredVelocity;
	
	for (Wall *w : walls)
	{
		if (IsObstacleAvoidance(agent, raycastVector, w, intersectionPoint,normalVector)) {
			avoidTarget = intersectionPoint;
			avoidTarget += normalVector * K_AVOIDANCE_DISTANCE;	
			desiredVelocity = avoidTarget - agent->getPosition();// Seek
		}
	}
	
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce.Normalize();

	return steeringForce * agent->getMaxForce();
}

void ObstacleAvoidance::setWalls(Wall* wall)
{
	walls.push_back(wall);
}

bool ObstacleAvoidance::IsObstacleAvoidance(Agent *agent, Vector2D raycast, Wall *w, Vector2D &intersectionPoint, Vector2D& normalVector)
{
	if (SegmentSegmentIntersection(agent->getPosition(), raycast,
		Vector2D(w->getPosition().x - w->getWeight(), w->getPosition().y - w->getHeight()),
		Vector2D(w->getPosition().x + w->getWeight(), w->getPosition().y - w->getHeight()), true, &intersectionPoint))
	{
		normalVector = Vector2D(0.f,-1.f);
		return true;
	}
	if (SegmentSegmentIntersection(agent->getPosition(), raycast,
		Vector2D(w->getPosition().x + w->getWeight(), w->getPosition().y - w->getHeight()), 
		Vector2D(w->getPosition().x + w->getWeight(), w->getPosition().y + w->getHeight()), true, &intersectionPoint))
	{
		normalVector = Vector2D(1.f, 0.f);
		return true;
	}
	if (SegmentSegmentIntersection(agent->getPosition(), raycast,
		Vector2D(w->getPosition().x + w->getWeight(), w->getPosition().y + w->getHeight()), 
		Vector2D(w->getPosition().x - w->getWeight(), w->getPosition().y + w->getHeight()), true, &intersectionPoint))
	{
		normalVector = Vector2D(0.f, 1.f);
		return true;
	}
	if (SegmentSegmentIntersection(agent->getPosition(), raycast,
		Vector2D(w->getPosition().x - w->getWeight(), w->getPosition().y + w->getHeight()), 
		Vector2D(w->getPosition().x - w->getWeight(), w->getPosition().y - w->getHeight()), true, &intersectionPoint))
	{
		normalVector = Vector2D(-1.f, 0.f);
		return true;
	}

	return false;
}
