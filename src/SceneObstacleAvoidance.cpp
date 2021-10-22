#include "SceneObstacleAvoidance.h"

SceneObstacleAvoidance::SceneObstacleAvoidance()
{
	srand(time(NULL)); // random seed

	Agent* agent;	// METER TODO EL CONTENIDO DE LOS AGENTES

	/*
	
	
	
	
	
	
	*/

	Wall* wall = new Wall();
	wall->setPosition(Vector2D(
		SDL_SimpleApp::Instance()->getWinSize().x / 2, 
		SDL_SimpleApp::Instance()->getWinSize().y / 2));

	walls.push_back(wall);
}

SceneObstacleAvoidance::~SceneObstacleAvoidance()
{
}

void SceneObstacleAvoidance::update(float dtime, SDL_Event* event)
{
}

void SceneObstacleAvoidance::draw()
{
	for (Wall *w : walls)
	{
		w->draw();
	}
}

const char* SceneObstacleAvoidance::getTitle()
{
	return "SDL Steering Behaviors :: Obstacle Avoidance with Flocking System";
}
