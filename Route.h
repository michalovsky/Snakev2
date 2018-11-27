#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Route :public Drawable
{
public:
	Route(Vector2f vel, Vector2f loc);
	Vector2f getVelocity() { return velocity; }
	Vector2f & setVelocity() { return velocity; }
	Vector2f getLocation() { return location; }
	Vector2f & setLocation() { return location; }
	int getVisitedNum() { return visitedNum; }
	int & setVisitedNum() { return visitedNum; }
private:
	int visitedNum{ 1 }; //starts with visited head
	Vector2f velocity{ 0,0 };
	Vector2f location{ 0,0 };
	RectangleShape shape;
	virtual void draw(RenderTarget & target, RenderStates state) const override;
};