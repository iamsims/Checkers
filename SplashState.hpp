#ifndef SPLASH_STATE_HPP
#define SPLASH_STATE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Board.hpp"
#include "MainMenuState.hpp"

namespace Checkers 
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data);
		void init();
		void handleInput();
		void update(float dt);
		void render(float dt);

	private:
		GameDataRef _data;
		sf::Clock _clock;
		sf::Sprite _background;
		sf::Vector2u backgroundTextureSize;
		sf::Vector2u windowSize ;
		int fadeAlpha = 255;
	};
}

#endif
