#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0), int flag=1);

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	void move(float xOffset, float yOffset);

    friend class Snake;

	void render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;


    sf::RectangleShape  body_shape_r;
	sf::CircleShape body_shape_c;
	static const float Height;
	static const float Width;
	static const float radius;
	static float angle_;
   

private:
    bool head_judge=false;
	sf::Sprite head_shape_;
	
	sf::Vector2f position_;
};
}

#endif