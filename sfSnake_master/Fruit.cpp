#include <SFML/Graphics.hpp>
#include <random>

#include "Fruit.h"



using namespace sfSnake;

const float Fruit::Radius = 7.f;

Fruit::Fruit(sf::Vector2f position)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	static std::random_device rd;
    std::mt19937 engine(rd());
	static std::uniform_int_distribution<int> generate_Distribution(0,200);
	int judge= generate_Distribution(engine);
	static sf::Color Brown (128, 64, 0);
	if(judge <= 25)
	shape_.setFillColor(sf::Color::Black);
	else if (judge <= 50)
	shape_.setFillColor(Brown);
	else if (judge <= 100)
	shape_.setFillColor(sf::Color::Red);
	else if (judge <= 150)
	shape_.setFillColor(sf::Color::Blue);
	else if (judge <= 200)
	shape_.setFillColor(sf::Color::Green);
	
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Color Fruit::GetfillColor() const
{
	return shape_.getFillColor();
}