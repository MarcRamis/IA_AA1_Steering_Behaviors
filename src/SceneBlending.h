#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Flee.h"
#include "Separation.h"
#include "Cohesion.h"
#include "Alignment.h"
#include "Seek.h"
#include "WeightedBlending.h"

class SceneBlending : public Scene
{
public:
	SceneBlending();
	~SceneBlending();
	void update(float dtime, SDL_Event* event);
	void draw();
	const char* getTitle();

private:
	std::vector<Agent*> agents;
	Vector2D target;
};