#pragma once

#include "Scene.h"
#include "Agent.h"
#include "Wall.h"
#include "Triangle.h"
#include "WeightedBlending.h"
#include "Seek.h"

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
    std::vector<Triangle*> triangles;
    Vector2D target;
};