#include <SFML/Graphics.hpp>
#include<iostream>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Height = 10.f;
const float SnakeNode::Width = 10.f;
const float SnakeNode::radius = 10.f;

sf::Texture pic1;
sf::Texture pic2;

SnakeNode::SnakeNode(sf::Vector2f position, int flag)
: position_(position)
{
    if(flag==0){
	head_judge=true;
	if(!pic1.loadFromFile("pic/h.png"))
     std::cout<<"error"<<std::endl;
	pic1.setSmooth(true);
	head_shape_.setTexture(pic1);
	head_shape_.setOrigin(head_shape_.getLocalBounds().width / 2, head_shape_.getLocalBounds().height / 2);
	head_shape_.setPosition(position.x+10.f, position.y+10.f);
	head_shape_.setScale(0.23,0.23);
	}
	else{
	body_shape_c.setFillColor(sf::Color::Yellow);
	body_shape_c.setPosition(position.x, position.y);
	body_shape_c.setRadius(radius);
    body_shape_r.setFillColor(sf::Color::Black);
	body_shape_r.setSize(sf::Vector2f(2*radius, radius/2));
	body_shape_r.setOrigin(radius, radius / 4);
	body_shape_r.setPosition(position.x + radius, position.y + radius);
	
	}
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	if(head_judge)
	head_shape_.setPosition(position_);
	else{
    body_shape_c.setPosition(position_);
	body_shape_r.setPosition(position_);
	}
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	if(head_judge)
	head_shape_.setPosition(position_);
	else{
    body_shape_c.setPosition(position_);
	body_shape_r.setPosition(position_);
	}
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	if(head_judge)
	head_shape_.setPosition(position_);
	else{
    body_shape_c.setPosition(position_);
	body_shape_r.setPosition(position_);
	}
}

sf::FloatRect SnakeNode::getBounds() const
{
	if(head_judge)
	return head_shape_.getGlobalBounds();
	else
	return body_shape_c.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	if(head_judge)
	window.draw(head_shape_);
	else{
    window.draw(body_shape_c);
	window.draw(body_shape_r);
	}
}

