#include "SceneBlending.h"

SceneBlending::SceneBlending()
{
	Agent* agent;

	for (int i = 0; i < 50; i++)
	{
		agent = new Agent;
		agent->setBehavior(new WeightedBlending({ new Seek, new Separation}, { new float(0.1f), new float(20.f)}));
		int randSpawnW = rand() % (1280);
		int randSpawnH = rand() % (768);
		agent->setPosition(Vector2D(randSpawnW, randSpawnH));
		agents.push_back(agent);
	}

	for (Agent * a : agents)
	{
		a->setTarget(Vector2D(640,360));
		a->loadSpriteTexture("../res/soldier.png", 4);
		target = Vector2D(640, 360);
	}

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
	srand(time(nullptr));

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
	return "SDL Steering Behaviors :: Blending";
}