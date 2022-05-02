#include "Wall.h"

Wall::Wall() : 
	position(Vector2D(300,300)), 
	weight(80.f), 
	height(80.f)
{
}

Wall::Wall(float _weight, float _height, Vector2D _pos) :
	position(_pos),
	weight(_weight),
	height(_height)
{
}

Wall::~Wall()
{
}

Vector2D Wall::getPosition()
{
	return position;
}

float Wall::getWeight()
{
	return weight;
}

float Wall::getHeight()
{
	return height;
}

void Wall::setPosition(Vector2D _position)
{
	position = _position;
}

void Wall::setWeight(float _weight)
{
	weight = _weight;
}

void Wall::setHeight(float _height)
{
	height = _height;
}

void Wall::draw()
{
	draw_cube(TheApp::Instance()->getRenderer(),(int)position.x  - weight / 2, (int)position.y  - height / 2, (int)weight, (int)height, 255, 0, 0, 255);
}
