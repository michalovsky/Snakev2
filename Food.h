#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
using namespace sf;

class Food : public Drawable
{
public:
	Food(int windowSizeX, int windowSizeY, float width, float height,const Snake & s);
	~Food() {}
	void newLocation(const Snake & s);
	bool isEaten(const Snake & s) const;
private:
	int x, y;
	int winDimX, winDimY;
	RectangleShape shape;
	void randomLocation();
	bool respawnCondition(const Snake & s);
	virtual void draw(RenderTarget & target, RenderStates state) const override;
};

