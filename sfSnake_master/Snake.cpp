#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 10;

Snake::Snake() : direction_(Direction(0,-1)), hitSelf_(false)
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/get.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::radius / 2,
			Game::Height / 2 - (SnakeNode::radius / 2) + (SnakeNode::radius * i * 1.5)),i));
	}
}

void Snake::handleInput(sf::RenderWindow& window)
{
	if (
	   (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||sf::Keyboard::isKeyPressed(sf::Keyboard::W)) &&
	   (direction_judge(Direction(0,-1))))
        direction_ = Direction(0,-1);
    else if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::S))&&
		(direction_judge(Direction(0,1))))
        direction_ = Direction(0,1);
    else if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A))&&
		(direction_judge(Direction(-1,0))))
        direction_ = Direction(-1, 0);
    else if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D))&&
		(direction_judge(Direction(1,0))))
        direction_ = Direction(1,0);
	else if (
         sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
         sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
		static sf::Vector2i MousePosition;	
		MousePosition = sf::Mouse::getPosition(window);
		Direction temp;
		temp.x =  MousePosition.x - nodes_[0].getPosition().x;
		temp.y =  MousePosition.y - nodes_[0].getPosition().y;
		float len = length(temp);
        if (len > 0)
        {
          temp /= len;
        }
		if(direction_judge(temp)){
		 direction_ = temp;
		}
	    }
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		sf::Color judge=(*toRemove).GetfillColor();
		static sf::Color Brown (128, 64, 0);
		if(judge==Brown||judge==sf::Color::Black)
		  ;
		if(judge==sf::Color::Green)
		    grow();
		if(judge==sf::Color::Blue){
			for(int i=0; i<2; i++)
			grow();
		}
		if(judge==sf::Color::Red){
			for(int i=0; i<3; i++)
			grow();
		}
		fruits.erase(toRemove);
	}
}

void Snake::grow()
{
    SnakeNode temp(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - direction_.x*SnakeNode::radius,
			nodes_[nodes_.size() - 1].getPosition().y - direction_.y*SnakeNode::radius));
    temp.body_shape_r.setRotation(nodes_[nodes_.size()-1].body_shape_r.getRotation());
    nodes_.push_back(temp);
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];
	for (decltype(nodes_.size()) i = 3; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
    
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	SnakeNode &headNode = nodes_.front();
	headNode=SnakeNode(sf::Vector2f(
        headNode.getPosition().x ,
        headNode.getPosition().y ));
    nodes_.push_front(SnakeNode(sf::Vector2f(
        headNode.getPosition().x + direction_.x  * 1.5 * SnakeNode::radius ,
        headNode.getPosition().y + direction_.y  * 1.5 * SnakeNode::radius ),0));
        
    nodes_.pop_back();
}

void Snake::render(sf::RenderWindow& window)
{
    SnakeNode& headNode = nodes_[0];
    SnakeNode& nextNode = nodes_[1];
    static sf::Vector2f recDirection;
    static float angle;
     recDirection= direction_;
    angle =
        std::acos(-recDirection.y / length(recDirection)) /
        3.14159265358979323846 * 180.0;
    if (direction_.x < 0)
        angle = -angle;
    headNode.head_shape_.setRotation(angle);
    nextNode.body_shape_r.setRotation(angle);
    for(auto node: nodes_){
        node.render(window);
    }
}

bool Snake::direction_judge(Direction direction) const{
    float angle_1 =
	   std::acos(direction_.y / length(direction_)) /
        3.14159265358979323846 * 180.0;
		if (direction_.x < 0)
        angle_1 = -angle_1; 
	float angle_2 =
        std::acos(direction.y / length(direction)) /
        3.14159265358979323846 * 180.0;
		if (direction.x < 0)
        angle_2 = -angle_2;
	angle_1 += 180;
	angle_2 += 180;
	if (angle_1 == 360)
     angle_1 = 0;
	if (angle_2 == 360)
     angle_2 = 0;
	if(fabs(angle_1 - angle_2) > 180)
     if(fabs(360 - fabs(angle_1 - angle_2))<= 90)
		return true;
	if(fabs(angle_1 - angle_2) < 180)
	  if(fabs(angle_1 - angle_2) <= 90)
        return true;   
    return false;
}