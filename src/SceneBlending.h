#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Flee.h"

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