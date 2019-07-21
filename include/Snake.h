#pragma once

#include "Block.h"
#include "Route.h"
#include <iostream>

class Snake : public Drawable
{
public:
	Snake(float windowSizeX, float windowSizeY, float blockWidth, float blockHeight);
	void update();
	void addTail();
	bool bodyCollision() const;
	bool wallsCollision() const;
	Vector2f getHeadPosition() const;
	std::vector<Block> getBody() const { return body; }
	int getBodySize() const { return bodySize; }
private:
	std::vector<Block> body; //body
 	std::vector<Route> route; //snake tracking system
	const float snakeVelocity{ 5.f }; 
	// recommended movement speed are: 1,2,3,5,6,10 
	//it wont work for others bcs of floats, havent finished mutual version of snake considering other speed
	int bodySize{ 1 };
	int width, height;
	void inputMovement();
	void bodyMovement();
	void trackingRoutes();
	void readMovementDirectionOfBody();
	bool upCondition();
	bool downCondition();
	bool rightCondition();
	bool leftCondition();
	void setWanna(bool & w);
	bool wannaLeft{ false }, wannaRight{ false }, wannaUp{ false }, wannaDown{ false };
	virtual void draw(RenderTarget & target, RenderStates state) const override;
};

