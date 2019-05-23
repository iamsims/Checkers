#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Board.hpp"

namespace Checkers
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);
		void init();
		void handleInput();
		void update(float dt);
		void render(float dt);

	private:
        bool mainmenu=1;
		GameDataRef _data;
		sf::Sprite _background;
		sf::Sprite _newgame;
		sf::Sprite _continue;
		sf::Sprite _exit;
		sf::Sprite _singlePlayer;
		sf::Sprite _twoPlayer;
		sf::Sprite _title;
	};
}

#endif
