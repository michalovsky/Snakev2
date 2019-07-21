#include "Snake.h"

Snake::Snake(float windowSizeX, float windowSizeY, float blockWidth, float blockHeight) :width(blockWidth), height(blockHeight)
{
	body.emplace_back(windowSizeX / 2, windowSizeY / 2, width, height, Vector2f{0,0});
}

Vector2f Snake::getHeadPosition() const
{
	return body[0].getcShape().getPosition();
}

void Snake::draw(RenderTarget & target, RenderStates state) const
{
	for (int i = 0; i < bodySize; i++) // draws cells of body
	{
		target.draw(body[i].getcShape(), state);
	}

	for(auto& node:route) // draws intersections
		target.draw(node,state);
}

void Snake::update() // update new data
{
	bodyMovement();
	trackingRoutes();
	readMovementDirectionOfBody();
	inputMovement();
}

void Snake::bodyMovement()
{
	for (int i = 0; i < bodySize; i++)
	{
		body[i].move(); //move whole body
		if (body[i].getVelocity() == Vector2f{ 0,0 } && i != 0)
		{
			if (abs(body[i - 1].getPosition().x - body[i].getPosition().x) >= 30
				|| abs(body[i - 1].getPosition().y - body[i].getPosition().y) >= 30)
			{
				body[i].setVelocity() = body[i].getFutureMovement();  //giving speed to tail
			}
		}
	}
}

void Snake::trackingRoutes()
{
	for (int i = 1; i < bodySize; i++) //routing, in place when head changing direction, there is addding a new object Route to std::vector<Route> route, this obj has location and vector of speed
	{
		for (int j = 0; j < route.size(); j++)
		{
			if (body[i].getPosition() == route[j].setLocation())
			{
				body[i].setVelocity() = route[j].getVelocity();
				route[j].setVisitedNum()++;
				if (route[j].getVisitedNum() == bodySize) // if all cells go through the point, point will be deleted
				{
					route[j].setLocation() = Vector2f{ -1000,-1000 };
				}
				break;
			}
		}
	}

	for (auto i = route.begin(); i != route.end(); ++i) //deleting routing
	{
		if ((*i).getLocation() == Vector2f{ -1000,-1000 }) route.erase(i);
		break;
	}
}

void Snake::readMovementDirectionOfBody()
{
	for (int i = 1; i < bodySize; i++) // reading movement direction from every cell of the body except from head
	{
		if (body[i].getPosition().x > body[i - 1].getPosition().x
			&& (body[i].getPosition().y == body[i - 1].getPosition().y)) body[i].setDirection(Block::left);
		else if (body[i].getPosition().x < body[i - 1].getPosition().x
			&& (body[i].getPosition().y == body[i - 1].getPosition().y)) body[i].setDirection(Block::right);
		else if (body[i].getPosition().y > body[i - 1].getPosition().y
			&& (body[i].getPosition().x == body[i - 1].getPosition().x)) body[i].setDirection(Block::up);
		else if (body[i].getPosition().y < body[i - 1].getPosition().y
			&& (body[i].getPosition().x == body[i - 1].getPosition().x)) body[i].setDirection(Block::down);
	}
}

void Snake::inputMovement() // simple giving head new movement direction by keyboard arrows up,down,right,left
{
	if (leftCondition())
	{
		if ((int)body[0].getPosition().x % 30 == 0
			&& (int)body[0].getPosition().y % 30 == 0)
		{
			body[0].setVelocity().x = -snakeVelocity;
			body[0].setVelocity().y = 0;
			body[0].setDirection(Block::left);
			if (bodySize > 1)
			{
				route.emplace_back(body[0].getVelocity(), body[0].getPosition());
			}
			wannaLeft = false;
		}
		else
		{
			setWanna(wannaLeft);
		}
	}
	else if (rightCondition())
	{
		if ((int)body[0].getPosition().x % 30 == 0
			&& (int)body[0].getPosition().y % 30 == 0)
		{
			body[0].setVelocity().x = snakeVelocity;
			body[0].setVelocity().y = 0;
			body[0].setDirection(Block::right);
			if (bodySize > 1)
			{
				route.emplace_back(body[0].getVelocity(), body[0].getPosition());
			}
			wannaRight = false;
		}
		else
		{
			setWanna(wannaRight);
		}
	}
	else if (upCondition())
	{
		if ((int)body[0].getPosition().x % 30 == 0
			&& (int)body[0].getPosition().y % 30 == 0)
		{
			body[0].setVelocity().x = 0;
			body[0].setVelocity().y = -snakeVelocity;
			body[0].setDirection(Block::up);
			if (bodySize > 1)
			{
				route.emplace_back(body[0].getVelocity(), body[0].getPosition());
			}
			wannaUp = false;
		}
		else
		{
			setWanna(wannaUp);
		}
	}
	else if (downCondition())
	{
		if ((int)body[0].getPosition().x % 30 == 0
			&& (int)body[0].getPosition().y % 30 == 0)
		{
			body[0].setVelocity().x = 0;
			body[0].setVelocity().y = snakeVelocity;
			body[0].setDirection(Block::down);
			if (bodySize > 1)
			{
				route.emplace_back(body[0].getVelocity(), body[0].getPosition());
			}
			wannaDown = false;
		}
		else
		{
			setWanna(wannaDown);
		}
	}
}

void Snake::setWanna(bool & w) // wish to turn somewhere
{
	wannaLeft = false;
	wannaRight = false;
	wannaUp = false;
	wannaDown = false;
	w=true;
}

void Snake::addTail() // set future movement, which is added when snake moves away and it will appear in the end
{
	switch (body[bodySize - 1].getDirection())
	{
	case Block::left:
		body.emplace_back(body[bodySize - 1].getPosition().x, body[bodySize - 1].getPosition().y, width, height, Vector2f{ 0,0 }, Vector2f{ -snakeVelocity,0 });
		break;
	case Block::right:
		body.emplace_back(body[bodySize - 1].getPosition().x, body[bodySize - 1].getPosition().y, width, height, Vector2f{ 0,0 }, Vector2f{ snakeVelocity,0 });
		break;
	case Block::up:
		body.emplace_back(body[bodySize - 1].getPosition().x, body[bodySize - 1].getPosition().y, width, height, Vector2f{ 0,0 }, Vector2f{ 0,-snakeVelocity });
		break;
	case Block::down:
		body.emplace_back(body[bodySize - 1].getPosition().x, body[bodySize - 1].getPosition().y, width, height, Vector2f{ 0,0 }, Vector2f{ 0, snakeVelocity });
		break;
	}
	bodySize++;
}

bool Snake::bodyCollision() const // checks if body and head are not in the common position
{
	for (int i = 1; i < bodySize; i++)
	{
		if (getHeadPosition().x == body[i].getPosition().x
			&& getHeadPosition().y == body[i].getPosition().y)
			return true;
	}
	return false;
}

bool Snake::wallsCollision() const // checks if head is not in wall
{
	return (getHeadPosition().x < 0 || getHeadPosition().x>870
		|| getHeadPosition().y < 0 || getHeadPosition().y>570);
}

bool Snake::upCondition() // up arrow pressed and not any more, and blocks to go opposite direction, also may go to remembered direction by wannaUp
{
	return ((Keyboard::isKeyPressed(Keyboard::Key::Up)
		&& body[0].getVelocity().y != snakeVelocity
		&& body[0].getVelocity().y != -snakeVelocity
		&& !Keyboard::isKeyPressed(Keyboard::Key::Right)
		&& !Keyboard::isKeyPressed(Keyboard::Key::Left)
		&& !Keyboard::isKeyPressed(Keyboard::Key::Down)) || wannaUp); //wannaUp means player wanted to go up but snake couldnt go earlier becouse of dimension of basic block 30x30px
}

bool Snake::downCondition()
{
	return ((Keyboard::isKeyPressed(Keyboard::Key::Down)
		&& body[0].getVelocity().y != snakeVelocity
		&& body[0].getVelocity().y != -snakeVelocity
		&& !Keyboard::isKeyPressed(Keyboard::Key::Right)
		&& !Keyboard::isKeyPressed(Keyboard::Key::Up)
		&& !Keyboard::isKeyPressed(Keyboard::Key::Left)) || wannaDown);
}

bool Snake::rightCondition()
{
	return ((Keyboard::isKeyPressed(Keyboard::Key::Right)
		&& body[0].getVelocity().x != -snakeVelocity
		&& body[0].getVelocity().x != snakeVelocity
		&& !Keyboard::isKeyPressed(Keyboard::Key::Left)
		&& !Keyboard::isKeyPressed(Keyboard::Key::Up)
		&& !Keyboard::isKeyPressed(Keyboard::Key::Down)) || wannaRight);
}

bool Snake::leftCondition()
{
	return ((Keyboard::isKeyPressed(Keyboard::Key::Left)
		&& body[0].getVelocity().x != snakeVelocity
		&& body[0].getVelocity().x != -snakeVelocity
		&& !Keyboard::isKeyPressed(Keyboard::Key::Right)
		&& !Keyboard::isKeyPressed(Keyboard::Key::Up)
		&& !Keyboard::isKeyPressed(Keyboard::Key::Down)) || wannaLeft);
}