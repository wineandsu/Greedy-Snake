#include <SFML/Graphics.hpp>

#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

std::string bg_color[]={"White","Black","Brown"};
std::string grid_color[]={"Black","White","Brown","Closed"};
std::string grid_switch[]={"Open","Open","Open","Closed"};

MenuScreen::MenuScreen()
{
	font_.loadFromFile("Fonts/my_ttf.ttf");
	text_.setFont(font_);
	text_.setColor(sf::Color::Black);
	text_.setScale(sf::Vector2f(1,1));
	text_.setString(
		"\n\n\n\n\n\n\n\n\nPress [SPACE] to play"
		"\n\nPress [ESC] to quit");

	snakeText_.setFont(font_);
	snakeText_.setString("Snake!");
	snakeText_.setScale(sf::Vector2f(2,2));
	snakeText_.setColor(sf::Color::Green);
	snakeText_.setCharacterSize(64);
	snakeText_.setStyle(sf::Text::Bold);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);

	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
		snakeTextBounds.top + snakeTextBounds.height / 2);
	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Game::Screen = std::make_shared<GameScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        GameScreen::bg_index = (GameScreen::bg_index + 1) % 3;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        GameScreen::grid_index = (GameScreen::grid_index + 1) % 3;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        GameScreen::grid_index = 3;
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
	std::string text_now =(
        "\n\n\n\nPress [SPACE] to play"
		"\n\nPress [ESC] to quit"
		"\n\nBefore playing:"
		"\n\nPress [Q] to switch \n\nbackground color to "+bg_color[GameScreen::bg_index]+
		"\n\nPress [W] to switch/open \n\ngrid color to "+grid_color[GameScreen::grid_index]+
		"\n\nPress [R] to close the grid");
    text_.setString(text_now);
}
void MenuScreen::render(sf::RenderWindow& window)
{
	b_render(window);
	window.draw(text_);
	window.draw(snakeText_);
}

void b_render(sf::RenderWindow& window){
	sf::RectangleShape shape_;
    shape_.setPosition(sf::Vector2f(0, 0));
    shape_.setFillColor(sf::Color::White);
    shape_.setSize(sf::Vector2f(Game::Width, Game::Height));
    window.draw(shape_);
}