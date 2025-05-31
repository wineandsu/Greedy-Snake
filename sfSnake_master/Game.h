#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>
#include <cmath>

#include "Screen.h"

namespace sfSnake
{
class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();

	static const int Width = 1280;
	static const int Height = 960;

	static std::shared_ptr<Screen> Screen;

	sf::RenderWindow get_window() const;

    
private:
	sf::RenderWindow window_;
	sf::Music bgMusic_;
    sf::Image icon;
	
	static const sf::Time TimePerFrame;
};
    template <typename T>
    inline double length(sf::Vector2<T> node) noexcept
    {
        return std::sqrt(
            std::pow(static_cast<double>(node.x), 2) +
            std::pow(static_cast<double>(node.y), 2));
    }

	template <typename T>
    inline sf::FloatRect setOriginMiddle(T &shape)
    {
        sf::FloatRect shapeBounds = shape.getLocalBounds();
        shape.setOrigin(shapeBounds.left + shapeBounds.width / 2,
                        shapeBounds.top + shapeBounds.height / 2);
        return shapeBounds;
    }


}


#endif