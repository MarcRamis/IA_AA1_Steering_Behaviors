#pragma once
#include "Vector2D.h"
#include "SDL_SimpleApp.h"
#include "utils.h"

class Triangle
{
private:
	Vector2D position, left, right, top;

public:

	Triangle();
	~Triangle();

	Vector2D getPosition();
	Vector2D getLeft();
	Vector2D getRight();
	Vector2D getTop();
	void setLeft(Vector2D _left);
	void setRight(Vector2D _right);
	void setTop(Vector2D _top);
	void draw();
};