#include "SceneObstacleAvoidance.h"

SceneObstacleAvoidance::SceneObstacleAvoidance()
{
	srand(time(NULL)); // random seed

	// Walls init
	Wall* wall = new Wall(100, 250, Vector2D(800, 300));
	Wall* wall2 = new Wall(100, 250, Vector2D(200, 300));

	walls.push_back(wall);
	walls.push_back(wall2);
	
	// Agents init
	Agent* agent;
	for (int i = 0; i < K_MAX_AGENTS; i++)
	{
		agent = new Agent;
		
		ObstacleAvoidance* sb_obstacleAvoidance = new ObstacleAvoidance;

		for (Wall* wall : walls)
		{
			sb_obstacleAvoidance->setWalls(wall);
		}
		WeightedBlending* sb_weightedBlending = new WeightedBlending({ new Seek,sb_obstacleAvoidance }, { new float(0.2f), new float(10.f) });
		agent->setBehavior(sb_weightedBlending);
		int randSpawnW = rand() % (1280);
		int randSpawnH = rand() % (768);
		agent->setPosition(Vector2D(randSpawnW, randSpawnH));

		agent->setTarget(Vector2D(640, 360));
		agent->loadSpriteTexture("../res/soldier.png", 4);
		agents.push_back(agent);
	}

	target = Vector2D(640, 360);

	// GET FLOCK & WALLS ON EVERY AGENT
	for (Agent* a : agents)
	{
		for (Agent *a2 : agents)
		{
			a->setFlock(a2);
		}
	}
}

SceneObstacleAvoidance::~SceneObstacleAvoidance()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	for (int i = 0; i < (int)walls.size(); i++)
	{
		delete walls[i];
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
