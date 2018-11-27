#include "Food.h"
#include "Block.h"
#include <ctime>
#include <cstdlib>

Food::Food(int windowSizeX, int windowSizeY, float width, float height, const Snake & s) 
{
	winDimX = windowSizeX;
	winDimY = windowSizeY;

	srand(time(NULL));
	randomLocation();

	shape.setSize(Vector2f{ width,height });
	shape.setFillColor(Color::Red);
}

void Food::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(shape, state);
}

void Food::newLocation(const Snake & s)
{
	while(respawnCondition(s))
		randomLocation();
}

bool Food::respawnCondition(const Snake & s)
{
	for (int i = 0; i < s.getBodySize(); i++)
	{
		if (x == (int)s.getBody()[i].getPosition().x
			&& y == (int)s.getBody()[i].getPosition().y) return true;
	}
	return false;
}


void Food::randomLocation()
{
	x = rand() % (winDimX - 30) + 30;
	y= rand() % (winDimY - 30) + 30;
	while ((x % 30 != 0) || (y % 30 != 0))
	{
		x = rand() % (winDimX - 30) + 30;
		y = rand() % (winDimY - 30) + 30;
	}
	shape.setPosition(x, y);
}

bool Food::isEaten(const Snake & s) const
{
		if (x == (int)s.getHeadPosition().x && y == (int)s.getHeadPosition().y) return true;
	return false;
}