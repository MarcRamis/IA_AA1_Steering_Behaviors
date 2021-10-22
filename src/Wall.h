#pragma once
#include "Vector2D.h"
#include "SDL_SimpleApp.h"
#include "utils.h"

class Wall
{
private:
	Vector2D position;
	float weight, height;

public:
	
	Wall();
	~Wall();

	Vector2D getPosition();
	float getWeight();
	float getHeight();
	void setPosition(Vector2D _position);
	void setWeight(float _weight);
	void setHeight(float _height);
	void draw();
};