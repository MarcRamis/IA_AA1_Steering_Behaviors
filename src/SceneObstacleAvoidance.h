#pragma once

#include "Scene.h"
#include "Agent.h"
#include "Wall.h"

#include "PriorityList.h"
#include "WeightedBlending.h"
#include "Seek.h"
#include "Flee.h"
#include "Separation.h"
#include "Cohesion.h"
#include "Alignment.h"
#include "ObstacleAvoidance.h"

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