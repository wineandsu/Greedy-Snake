#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "GameOverScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score)
{
	font_.loadFromFile("Fonts/my_ttf.ttf");
	text_.setFont(font_);
	text_.setScale(sf::Vector2f(1.5,1.5));
	text_.setString("Your score: " + std::to_string(score) + "!"
		"\n\nPress [SPACE] to retry"
		"\n\nPress [ESC] to quit"
		"\n\nPress [R] to return to the menu");
	text_.setColor(sf::Color::Green);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Game::Screen = std::make_shared<GameScreen>();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	    Game::Screen = std::make_shared<MenuScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
}

void GameOverScreen::update(sf::Time delta)
{

}

void GameOverScreen::render(sf::RenderWindow& window)
{
	b_o_render(window);
	window.draw(text_);
}

void b_o_render(sf::RenderWindow& window){
	sf::RectangleShape shape_;
    shape_.setPosition(sf::Vector2f(0, 0));
    shape_.setFillColor(sf::Color::White);
    shape_.setSize(sf::Vector2f(Game::Width, Game::Height));
    window.draw(shape_);
}