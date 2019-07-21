#include "Snake.h"
#include "Food.h"

int main()
{
	RenderWindow window{ VideoMode{900,600},"snake-sfml" };

	sf::Texture texture;
	if (!texture.loadFromFile("../stuff/grass.jpg"))
	{
		std::cout << "Load failed" << std::endl;
		return 1;
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 900, 600));

	window.setFramerateLimit(60);
	Event event;

	Snake snake(900, 600, 30, 30);
	Food food(900, 600, 30, 30, snake);
	while (true)
	{
		window.clear(Color::White);
		window.pollEvent(event);

		if (event.type == Event::Closed)
		{
			window.close();
			break;
		}

		window.draw(sprite);

		snake.update();
		if (snake.bodyCollision() ||snake.wallsCollision()) break;

		if (food.isEaten(snake))
		{
			food.newLocation(snake);
			snake.addTail();
			snake.update();
		}

		window.draw(food);
		window.draw(snake);
		window.display();
	}
	return 0;
}