#pragma once
#include <SFML/Graphics.hpp>

namespace Checkers{
	class InputManager{
	public:
		InputManager() {}

		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);

		sf::Vector2i GetMousePosition(sf::RenderWindow &window);
	};
}
