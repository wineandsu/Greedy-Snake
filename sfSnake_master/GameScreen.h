#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	void generateFruit();

    static int bg_index;
	static int grid_index;

private:
	Snake snake_;
	std::vector<Fruit> fruit_;
};
}
void backg_render(sf::RenderWindow& window);
void grid_line_render(sf::RenderWindow& window);

#endif