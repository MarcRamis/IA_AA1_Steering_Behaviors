#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneBlending : public Scene
{
public:
	SceneBlending();
	~SceneBlending();
	void update(float dtime, SDL_Event* event);
	void draw();

private:
	std::vector<Agent*> agents;
};