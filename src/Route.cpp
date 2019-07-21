#include "Route.h"

Route::Route(Vector2f vel, Vector2f loc) : velocity(vel), location(loc)
{
	shape.setPosition(location.x, location.y);
	shape.setSize(Vector2f{ 30,30 });
	shape.setFillColor(Color::Black);
}

void Route::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(shape, state);
}