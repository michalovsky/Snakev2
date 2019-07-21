#include "Block.h"

Block::Block(float x, float y, float width, float height, Vector2f v, Vector2f fv)
{
	shape.setPosition(x, y);
	shape.setSize(Vector2f{ width,height });
	shape.setFillColor(Color::Black);
	velocity = v;
	futureMovement = fv;
}

void Block::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(shape, state);
}

Vector2f Block::getPosition() const
{
	return shape.getPosition();
}

void Block::setDirection(int direction)
{
	directionNum = direction;
}

void Block::move()
{
	shape.move(velocity);
}