#include "Triangle.h"

Triangle::Triangle() :
	left(Vector2D(300, 300)),
	right(Vector2D(300, 300)),
	top(Vector2D(300, 300))
{
}

Triangle::~Triangle()
{
}

Vector2D Triangle::getPosition()
{
	position.x = (left.x + right.x, top.x) / 3;
	position.y = (left.y + right.y, top.y) / 3;
	return position;
}

Vector2D Triangle::getLeft()
{
	return left;
}

Vector2D Triangle::getRight()
{
	return right;
}

Vector2D Triangle::getTop()
{
	return top;
}

void Triangle::setLeft(Vector2D _left)
{
	left = _left;
}

void Triangle::setRight(Vector2D _right)
{
	right = _right;
}

void Triangle::setTop(Vector2D _top)
{
	top = _top;
}

void Triangle::draw()
{
	draw_triangle(TheApp::Instance()->getRenderer(), (int)left.x, (int)left.y, (int)right.x, (int)right.y, (int)top.x, (int)top.y, 0, 255, 0, 255);
}
