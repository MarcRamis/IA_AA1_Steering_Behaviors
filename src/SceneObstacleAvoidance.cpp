#include "SceneObstacleAvoidance.h"

SceneObstacleAvoidance::SceneObstacleAvoidance()
{
	srand(time(NULL)); // random seed

	Agent* agent;	// METER TODO EL CONTENIDO DE LOS AGENTES

	for (int i = 0; i < K_MAX_AGENTS; i++)
	{
		agent = new Agent;
		agent->setBehavior(new WeightedBlending(
			{ new Seek }, 
			{ new float(1) }));
		int randSpawnW = rand() % (1280);
		int randSpawnH = rand() % (768);
		agent->setPosition(Vector2D(randSpawnW, randSpawnH));

		agent->setTarget(Vector2D(640, 360));
		agent->loadSpriteTexture("../res/soldier.png", 4);
		agents.push_back(agent);
	}

	target = Vector2D(640, 360);

	for (Agent* a : agents)
	{
		for (Agent *a2 : agents)
		{
			a->setFlock(a2);
		}
	}

	Wall* wall = new Wall();
	wall->setPosition(Vector2D(
		SDL_SimpleApp::Instance()->getWinSize().x / 2, 
		SDL_SimpleApp::Instance()->getWinSize().y / 2));

	walls.push_back(wall);
}

SceneObstacleAvoidance::~SceneObstacleAvoidance()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneObstacleAvoidance::update(float dtime, SDL_Event* event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));

			for (Agent* a : agents)
			{
				a->setTarget(target);
			}
		}
		break;
	default:
		break;
	}

	for (Agent* a : agents)
	{
		a->update(dtime, event);
	}
}

void SceneObstacleAvoidance::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);

	for (Agent* a : agents)
	{
		a->draw();
	}

	for (Wall *w : walls)
	{
		w->draw();
	}
}

const char* SceneObstacleAvoidance::getTitle()
{
	return "SDL Steering Behaviors :: Obstacle Avoidance with Flocking System";
}
