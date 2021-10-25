#include "SceneBlending.h"

SceneBlending::SceneBlending()
{
	srand(time(NULL)); // random seed

	Agent* agent;

	for (int i = 0; i < K_MAX_AGENTS; i++)
	{
		agent = new Agent;

		WeightedBlending* sb_weightedBlending = new WeightedBlending(
			{ new Separation, new Cohesion, new Alignment },
			{ new float(0.60f), new float(0.20f), new float(0.20f) });
		PriorityList* sb_priorityList = new PriorityList();
		agent->setBehavior(new PriorityList({ sb_weightedBlending, new Seek, new Flee}));

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
}

SceneBlending::~SceneBlending()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneBlending::update(float dtime, SDL_Event* event)
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

void SceneBlending::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);

	for (Agent* a : agents)
	{
		a->draw();
	}
}

const char* SceneBlending::getTitle()
{
	return "SDL Steering Behaviors :: Flocking system";
}