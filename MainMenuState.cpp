#include "MainMenuState.hpp"

#include <sstream>
#include "GameState.hpp"
#include <iostream>

#define SCREEN_WIDTH 537
#define SCREEN_HEIGHT 537

namespace Checkers
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data){}

	void MainMenuState::init()
	{
		_data->assets.loadTexture("Background", "assets/menubackground.png");
		_data->assets.loadTexture("Single Player", "assets/1player.png");
		_data->assets.loadTexture("Two Player", "assets/2player.png");
		_data->assets.loadTexture("New Game","assets/newgame.png");
        _data->assets.loadTexture("Continue","assets/loadgame.png");
        _data->assets.loadTexture("Exit", "assets/exit.png");

		_background.setTexture(_data->assets.getTexture("Background"));
		_singlePlayer.setTexture(_data->assets.getTexture("Single Player"));
		_twoPlayer.setTexture(_data->assets.getTexture("Two Player"));
		_newgame.setTexture(_data->assets.getTexture("New Game"));
        _continue.setTexture(_data->assets.getTexture("Continue"));
		_exit.setTexture(_data->assets.getTexture("Exit"));


		_singlePlayer.setPosition((SCREEN_WIDTH / 2) - (_singlePlayer.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 3) - (_singlePlayer.getGlobalBounds().height / 2));
		_twoPlayer.setPosition((SCREEN_WIDTH / 2) - (_singlePlayer.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_singlePlayer.getGlobalBounds().height / 2));
        _newgame.setPosition((SCREEN_WIDTH / 2) - (_newgame.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 3) - (_newgame.getGlobalBounds().height / 2));
        _continue.setPosition((SCREEN_WIDTH / 2) - (_continue.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 3 + 100) - (_continue.getGlobalBounds().height / 2));
        _exit.setPosition((SCREEN_WIDTH / 2) - (_exit.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 3 + 200) - (_exit.getGlobalBounds().height / 2));

	}

	void MainMenuState::handleInput(){
		sf::Event event;
		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}


			if (mainmenu)
            {

            if(_data->input.IsSpriteClicked(_newgame, sf::Mouse::Left, _data->window))
			{
            mainmenu=0;
            }

            if(_data->input.IsSpriteClicked(_continue, sf::Mouse::Left, _data->window))
			{
             _data->machine.addState(StateRef(new GameState(_data , 2)),true);   //2 for continue
            }

            if(_data->input.IsSpriteClicked(_exit, sf::Mouse::Left, _data->window))
			{
            _data->window.close();
            }
            }

            else
            {
			if (_data->input.IsSpriteClicked(_twoPlayer, sf::Mouse::Left, _data->window))
			{
				_data->machine.addState(StateRef(new GameState(_data, 0)), true);
			}

			if (_data->input.IsSpriteClicked(_singlePlayer, sf::Mouse::Left, _data->window))
			{
				_data->machine.addState(StateRef(new GameState(_data, 1)), true);
			}

            }


		}
	}

	void MainMenuState::update(float dt){

	}

	void MainMenuState::render(float dt){
		_data->window.clear(sf::Color::Red);
		_data->window.draw(_background);

		if(mainmenu)
        {
        _data->window.draw(_newgame);
        _data->window.draw(_continue);
        _data->window.draw(_exit);
        }
        else
        {
		_data->window.draw(_singlePlayer);
		_data->window.draw(_twoPlayer);
        }

		_data->window.draw(_title);
		_data->window.display();
	}
}
