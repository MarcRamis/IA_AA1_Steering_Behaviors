#pragma once

#include "Constants.h"
#include "Utility.h"

#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"

#include <vector>

class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual Vector2D calculateSteeringForce(Agent* agent, float dtime) = 0;
		Vector2D GetSteeringForce(Agent* agent, float dtime);
		void applySteeringForce(Agent *agent, float dtime) {
			Vector2D steeringForce = this->calculateSteeringForce(agent, dtime);
			Vector2D acceleration = steeringForce / agent->getMass();
			Vector2D velocity = agent->getVelocity() + acceleration * dtime;
			velocity.Normalize();
			velocity *= agent->getMaxVelocity();
			agent->setVelocity(velocity);
			agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
		};
	};

private:
	
	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;
	std::vector<Agent*> flock;
	std::vector<Agent*> neighbour_Flock;

	float mass;
	float speed;
	float orientation;
	float max_force;
	float max_velocity;
	float slowingRadius;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

public:

	Agent();
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	float getSlowingRadius();
	std::vector<Agent*> getNeighbour_flock();
	void setFlock(Agent *agent);
	void setBehavior(SteeringBehavior *behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);

private:
	void setNeighbourFlock(const float neghbour_radius);
	void cleanNeighbourFlock();
};
