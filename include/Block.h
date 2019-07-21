#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Block : public Drawable
{
public:
	Block(float x, float y, float width, float height, Vector2f v = { 0,0 }, Vector2f fv = { 0,0 });
	Vector2f getPosition() const;
	RectangleShape & getShape() { return shape; }
	RectangleShape getcShape() const { return shape; }
	void setDirection(int direction);
	int getDirection() const { return directionNum; }
	enum direction{up=0,down=1,right=2,left=3};
	Vector2f & setVelocity(){ return velocity; }
	Vector2f getVelocity() { return velocity; }
	Vector2f getFutureMovement() { return futureMovement; }
	Vector2f & setFutureMovement() { return futureMovement; }
	void move();
private:
	int directionNum;
	Vector2f futureMovement{ 0,0 };
	virtual void draw(RenderTarget & target, RenderStates state) const override;
	RectangleShape shape;
	Vector2f velocity{ 0,0 };
};

