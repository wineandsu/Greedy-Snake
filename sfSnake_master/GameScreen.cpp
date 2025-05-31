#include <SFML/Graphics.hpp>

#include <random>
#include<iostream>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

sf::Color bg_color[3]={sf::Color::White,sf::Color::Black,
sf::Color(128,64,0)};
sf::Color grid_color[4]={sf::Color::Black,sf::Color::White,
sf::Color(128,64,0),sf::Color::Transparent};

int GameScreen::bg_index=0;
int GameScreen::grid_index=0;

GameScreen::GameScreen() : snake_()
{

}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() <= 5)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	backg_render(window);
	grid_line_render(window);
	snake_.render(window);
	for (auto fruit : fruit_){
		fruit.render(window);
	}
}

void GameScreen::generateFruit()
{
	static std::random_device rd;
    std::mt19937 engine(rd());
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);
	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine))));
}

void backg_render(sf::RenderWindow& window){	
    sf::RectangleShape shape_;
    shape_.setPosition(sf::Vector2f(0, 0));
    shape_.setFillColor(bg_color[GameScreen::bg_index]);
    shape_.setSize(sf::Vector2f(Game::Width, Game::Height));
    window.draw(shape_);
}

void grid_line_render(sf::RenderWindow& window){
	for (int y = SnakeNode::Height; y < Game::Height;y += 2*SnakeNode::Height) {
        sf::RectangleShape row_line;
        row_line.setPosition(sf::Vector2f(0, y));
        row_line.setFillColor(grid_color[GameScreen::grid_index]);
        row_line.setSize(sf::Vector2f(Game::Width, -1.0f));
        window.draw(row_line);
    }
	for (int x = SnakeNode::Width; x < Game::Width;x += 2*SnakeNode::Width) {
        sf::RectangleShape col_line;
        col_line.setPosition(sf::Vector2f(x, 0));
        col_line.setFillColor(grid_color[GameScreen::grid_index]);
        col_line.setSize(sf::Vector2f(-1.0f, Game::Height));
        window.draw(col_line);
    }
}
