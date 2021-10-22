#pragma once

#include "Scene.h"
#include "Agent.h"
#include "Wall.h"

class SceneObstacleAvoidance :
    public Scene
{
public:
    SceneObstacleAvoidance();
    ~SceneObstacleAvoidance();
    void update(float dtime, SDL_Event* event);
	void draw();
	const char* getTitle();

private:
    
    std::vector<Agent*> agents;
    std::vector<Wall*> walls;
    Vector2D target;
};