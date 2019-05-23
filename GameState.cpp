#include "GameState.hpp"
#include "Player.hpp"
#include "AI.hpp"

#include <sstream>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;

namespace Checkers {
	GameState::GameState(GameDataRef data, int mode)
		: _mboard(new Board()), _data(data)
		{
			if (mode==2) gamemode=_mboard->load();
			else
                {gamemode=mode;
			_mboard->setFirstPlayer(2);
			}

            _mboard->mode=gamemode;

			std::cout << "Gamestate initialized" << std::endl;
	}

	void GameState::init() {
		_data->assets.loadFont("FiraMono", "assets/FiraMono-Regular.otf");
		_data->assets.loadTexture("backgroundBoard", "assets/board.png");
		_data->assets.loadTexture("figures", "assets/webapp.png");
		// _data->assets.loadTexture("outerBoard", "assets/wooden_background.jpg");
		_data->assets.sound.openFromFile("assets/21.wav");

		initStats(_wcount, 504, 84);
		initStats(_bcount, 504, 430);

		// _outerBoard.setTexture(_data->assets.getTexture("outerBoard"));
		// _data->assets.getTexture("outerBoard").setRepeated(true);
		// _outerBoard.setPosition(0, 0);
		_board.setTexture(_data->assets.getTexture("backgroundBoard"));
		_board.setPosition(0, 0);

		initPosition();
		//if (gamemode!=2)_mboard->setFirstPlayer(2);
		std::cout<<"init called ";
		     //if continue not done only then the first player is set
	}

	void GameState::initStats(sf::Text& text, int x, int y){
		text.setFont(_data->assets.getFont("FiraMono"));
		text.setCharacterSize(20);
		text.setStyle(sf::Text::Bold);
		text.setColor(sf::Color::Blue);
		text.setPosition(x, y);
	}

	void GameState::initPosition(){
		for (int i = 0; i < temp; ++i){
			_figures[i].setTexture(_data->assets.getTexture("figures"));
		}
		int k=0;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if (_mboard->cell[i][j].getTYPE() == WHITE_PAWN ){
					_figures[k].setTextureRect(sf::IntRect(0,0,56,56));
					_figures[k].setPosition(56*j,56*i);
					k++;
				}else if(_mboard->cell[i][j].getTYPE()  == YELLOW_PAWN){
					_figures[k].setTextureRect(sf::IntRect(56,0,56,56));
					_figures[k].setPosition(56*j,56*i);
					k++;
				}
				else if(_mboard->cell[i][j].getTYPE()  == WHITE_KING){
					_figures[k].setTextureRect(sf::IntRect(112,0,56,56));
					_figures[k].setPosition(56*j,56*i);
					k++;
				}
				else if(_mboard->cell[i][j].getTYPE()  == YELLOW_KING){
					_figures[k].setTextureRect(sf::IntRect(168,0,56,56));
					_figures[k].setPosition(56*j,56*i);
					k++;
				}
			}
		}
		temp = k;
	}

	void GameState::handleInput() {
		sf::Vector2i pos = sf::Mouse::getPosition(_data->window) - sf::Vector2i(offset);
		sf::Event evt;
		while (_data->window.pollEvent(evt)) {
			if (sf::Event::Closed == evt.type) {
				savemode=1;
				std::cout<<"savemode on ";
			}


				if(evt.type==sf::Event::KeyPressed &&savemode)
           {
            if (evt.key.code == sf::Keyboard::S)
            {
                std::cout<<"uhhhu  i am here "<<std::endl;
                _mboard->save();
                _data->window.close();
            }

            if (evt.key.code == sf::Keyboard::Escape)
            {
                std::cout<<"also me babe"<<std::endl;
                _data->window.close();
            }


		   }

			if (evt.type == sf::Event::MouseButtonPressed){
				if (evt.mouseButton.button == sf::Mouse::Left){
					for(int i=0;i<temp;i++){
						if (_figures[i].getGlobalBounds().contains(pos.x,pos.y))
						{
							_mboard->_isMoving = true;
							_selectedPieceIndex=i;
							dx=pos.x - _figures[i].getPosition().x;
							dy=pos.y - _figures[i].getPosition().y;
							currentPosition  =  _figures[i].getPosition();
							_mboard->_isMoving = _mboard->selectCell((int)currentPosition.y/56,(int)currentPosition.x/56 );

						}
					}
				}
			}

			if (evt.type == sf::Event::MouseButtonReleased)
				if (evt.mouseButton.button == sf::Mouse::Left)
				{
					if(!_mboard->_isMoving){
						return;
					}
					_mboard->_isMoving = false;
					sf::Vector2f position = _figures[_selectedPieceIndex].getPosition() + sf::Vector2f(56/2,56/2);
					newPos= sf::Vector2f( 56*int(position.x/56), 56*int(position.y/56) );
					int fx=newPos.x/56, fy=newPos.y/56;
					if(_mboard->mover(fy, fx)){
						_data->assets.sound.play();
	 					 _mboard->validmultiplecheck=_mboard->multipleMoveValid();
						 if(!_mboard->validmultiplecheck)
						 {
						 	_mboard->alterTurn();
						 }
						 else
						 {
							_mboard->xinmultiple=_mboard->xCoordSelectedCell;
							_mboard->yinmultiple=_mboard->yCoordSelectedCell;
						 }
						 if (_mboard->validmultiplecheck&&_mboard->updatevar==1)
						 {
              _mboard->alterTurn();
							_mboard->validmultiplecheck=false;
						 }

						 checkConditionall();

						 if ((gamemode==1) && (_mboard->currentPlayer.getcolour() == Player::WHITE)){
							 auto move = AI::getBestMove(6, *_mboard, false);
							 for(auto& coords : move.coords){
								 _mboard->move(coords);
							 };
                   _mboard->alterTurn();
						 }

						_figures[_selectedPieceIndex].setPosition(newPos);
						initPosition();
					}else{
						_figures[_selectedPieceIndex].setPosition(currentPosition);
					}
					// cout << *_mboard;
				}
		update(1.0f/30.0f);
		}

		if (_mboard->_isMoving){
			_figures[_selectedPieceIndex].setPosition(pos.x-dx,pos.y-dy);
		}
	}

	void GameState::update(float dt) {

	     if (savemode==1)
            {
                _savegame.setFont(_data->assets.getFont("FiraMono"));
		        _savegame.setCharacterSize(20);
                _savegame.setStyle(sf::Text::Bold);
                _savegame.setColor(sf::Color::Blue);
		        _savegame.setPosition(60,_data->window.getSize().y/2);
		        _savegame.setString("Press S to save the game \n OR \n Esc to exit");

            }
			 checkConditionall();

	}
	
	void GameState::checkConditionall(){
		int temp = _mboard->checkWin();
		if ( temp == -1 )
		{
			_mboard->alterTurn();
			showGameOver();
		}else if ( temp == 1 ){
			showGameOver();
		}
	}

	void GameState::showGameOver(){
			rectangle.setSize(sf::Vector2f(400.0f,120.0f));
			rectangle.setFillColor(sf::Color::Black);
			rectangle.setPosition(57,_data->window.getSize().y/2-2);
			_gameover.setFont(_data->assets.getFont("FiraMono"));
			if (_mboard->currentPlayer.getcolour()==_mboard->player1.getcolour())
			{
					_gameover.setString("White wins");
			}
			else
			{
						_gameover.setString("Yellow wins");
			}

			_gameover.setCharacterSize(50);
			_gameover.setStyle(sf::Text::Bold);
			_gameover.setColor(sf::Color::White);
			_gameover.setPosition(60,_data->window.getSize().y/2);
	}

	void GameState::render(float dt) {
		// _data->window.clear(sf::Color(218, 166, 115));
		_data->window.draw(_board);
		// _data->window.draw(_outerBoard);

		for (int i = 0; i < temp; ++i)
		{
			_figures[i].move(offset);
			_data->window.draw(_figures[i]);
			_figures[i].move(-offset);
		}

		_data->window.draw(_wcount);
		_data->window.draw(_bcount);
		_data->window.draw(rectangle);
		_data->window.draw(_gameover);
        _data->window.draw(_savegame);
		_data->window.display();
	}
}
