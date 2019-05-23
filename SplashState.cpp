#include <sstream>
#include "Game.hpp"
#include "GameState.hpp"
#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include <iostream>

namespace Checkers
{
	SplashState::SplashState(GameDataRef data) : _data(data){}

	void SplashState::init(){
		_data->assets.loadTexture("splash_state_background", "assets/splashstate.jpg");
		backgroundTextureSize =	_data->assets.getTexture("splash_state_background").getSize();
		_data->assets.loadTexture("Two Player", "assets/2playerpressed.png");
    windowSize = _data->window.getSize();
    float ScaleX = (float) windowSize.x / backgroundTextureSize.x;
    float ScaleY = (float) windowSize.y / backgroundTextureSize.y; 

		// _background.setTexture(_data->assets.getTexture("Two Player"));
		_background.setTexture(_data->assets.getTexture("splash_state_background"));
    _background.setScale(ScaleX, ScaleY);   
	}

	void SplashState::handleInput(){
		sf::Event event;
		while (_data->window.pollEvent(event)){
			if (sf::Event::Closed == event.type){
				_data->window.close();
			}
		}
	}

	void SplashState::update(float dt){
		_background.setColor(sf::Color(255, 255, 255, fadeAlpha));
		fadeAlpha-=2;
		if (_clock.getElapsedTime().asSeconds() > 3){
			// std::cout << "transition of state" << std::endl;
         _data->machine.addState(StateRef(new MainMenuState(_data)));
       // _data->machine.addState(StateRef(new GameState(_data)));
		}
	}

	void SplashState::render(float dt){
		_data->window.clear(sf::Color::Black);
		_data->window.draw(_background );
		_data->window.display();
	}

}
