#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <deque>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
  using Direction=sf::Vector2f;

class Snake
{
public:
	Snake();

	void handleInput(sf::RenderWindow& window);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	void checkFruitCollisions(std::vector<Fruit>& fruits);
	sf::Vector2f toWindow(sf::Vector2f node);

	bool hitSelf() const;
	bool direction_judge(Direction direction) const;

	unsigned getSize() const;

private:
	void move();
	void grow();
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();

	bool hitSelf_;

	sf::Vector2f position_;
	sf::Vector2f direction_;

	sf::Sprite headSprite;
	

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	std::deque<SnakeNode> nodes_;

	static const int InitialSize;
};
}

#endif