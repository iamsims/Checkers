#include <sstream>
#include "GameState.hpp"
#include "PauseState.hpp"


#include <iostream>
using namespace std;


namespace Checkers {
    GameState::GameState(GameDataRef data)
        : _data(data) { }



    void GameState::init() {
        _data->assets.loadFont("FiraMono", "assets/FiraMono-Regular.otf");
        _data->assets.loadTexture("background_board", "assets/board.png");
        _data->assets.loadTexture("figures", "assets/webapp.png");

        _text.setFont(_data->assets.getFont("FiraMono"));
        _text.setString("Esc to Pause");
        _text.setCharacterSize(24);
        _text.setFillColor(sf::Color::Black);
        _text.setPosition(4, _data->window.getSize().y - 30);
#ifdef DEBUG
        _stats.setFont(_data->assets.getFont("FiraMono"));
        _stats.setCharacterSize(12);
        _stats.setFillColor(sf::Color::Black);
        _stats.setPosition(4, 4);
#endif
        _board.setTexture(_data->assets.getTexture("background_board"));
        _board.setPosition(0, 0);


        for (int i = 0; i < 24; ++i)
        {
            _figures[i].setTexture(_data->assets.getTexture("figures"));
        }

        // for (int i = 0; i < 16; ++i)
        // {
        //     _data->gameState[i] = -6;
        // }

        // for (int i = 16; i < 48; ++i)
        // {
        //     _data->gameState[i] = 0;
        // }

        // for (int i = 48; i < 64; ++i)
        // {
        //     _data->gameState[i] = 6;
        // }

        // _data->gameState = { 0,-1,0,-1,0,-1,0,-1, 
        //{ 0,-1,0,-1,0,-1,0,-1, 
        //                         -1,0,-1,0,-1,0,-1,0,
         //                        0,-1,0,-1,0,-1,0,-1,
          //                       0, 0, 0, 0, 0, 0, 0, 0,
         //                        0, 0, 0, 0, 0, 0, 0, 0,
        //                         1, 0, 1, 0, 1, 0, 1, 0, 
        //                         0, 1, 0, 1, 0, 1, 0, 1,
        //                         1, 0, 1, 0, 1, 0, 1, 0
        //                     };
        

        int k=0;
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
            {
                int n = _data->gameState[j+8*i];
                if (!n) continue;
                int x = n>0 ? 1:0;
                int y = abs(n)-1;
                _figures[k].setTextureRect( sf::IntRect(56*x,56*y,56,56) );
                _figures[k].setPosition(56*j,56*i);
                k++;
            }
        }

        int BoardState[8][8]={ {0,1,0,0,0,-1,0,-1}, 
                        {1,0,1,0,0,0,-1,0},
                        {0,1,0,0,0,-1,0,-1},
                        {1, 0,1, 0, 0, 0,-1, 0},
                        {0, 1, 0, 0, 0,-1, 0,-1},
                        {1, 0, 1, 0,0, 0, -1, 0}, 
                        {0,1, 0,0, 0, -1, 0, -1},
                        {1, 0, 1, 0,0, 0, -1, 0}
                            };


    std::string GameState::moveNote(sf::Vector2f p){
        std::string s = " ";
        s += char(p.x/56+97);
        s += char(7-p.y/56+49);
        return s;
    }

    void GameState::handleInput() {
        sf::Vector2i pos = sf::Mouse::getPosition(_data->window) - sf::Vector2i(offset);
        sf::Event evt;
        while (_data->window.pollEvent(evt)) {
            if (sf::Event::Closed == evt.type) {
                _data->window.close();
            }

            if (sf::Event::KeyPressed == evt.type) {
                if (sf::Keyboard::Escape == evt.key.code) {
                    _data->machine.addState(StateRef(new PauseState(_data)),
                            false);
                }
            }

            if (evt.type == sf::Event::MouseButtonPressed)
                if (evt.key.code == sf::Mouse::Left)
                    for(int i=0;i<32;i++)
                        if (_figures[i].getGlobalBounds().contains(pos.x,pos.y))
                        {
                            isMove=true; n=i;
                            dx=pos.x - _figures[i].getPosition().x;
                            dy=pos.y - _figures[i].getPosition().y;
                            oldPos  =  _figures[i].getPosition();
                        }

            if (evt.type == sf::Event::MouseButtonReleased)
                if (evt.key.code == sf::Mouse::Left)
                {
                    isMove=false;
                    sf::Vector2f p = _figures[n].getPosition() + sf::Vector2f(56/2,56/2);
                    newPos = sf::Vector2f( 56*int(p.x/56), 56*int(p.y/56) );
                    str = moveNote(oldPos)+moveNote(newPos);

                    if ((int(newPos.x)+int(newPos.y))%112==0)
                    {
                        newPos=oldPos;

                    }
                    for (int j=0;j<24;j++)
                    {
                        if (_figures[n].getGlobalBounds().intersects(_figures[j].getGlobalBounds()))
                        {
                            if (n!=j)
                            {
                            newPos=oldPos;
                            break;
                            }
                        }
                    }
                   int ix=oldPos.x/56,iy=oldPos.y/56 ,fx=newPos.x/56,    fy=newPos.y/56;
                    int temp=BoardState[ix][iy];
                  BoardState[ix][iy]=BoardState[fx][fy];
                    BoardState[fx][fy]=temp;
 //                    for (int i=0;i<8;i++)
//                    {
              //          for (int j=0;j<8;j++)
             //           {
  //                          cout<<setw(3)<<BoardState[j][i];
  //                      }
  //                      cout<<"\n";
 //                   }
 //                   cout<<"   \n"     ; 



                    move(str); 
                    if (oldPos!=newPos) position+=str+" ";
                    _figures[n].setPosition(newPos);                   
                }                       
        }

        if (isMove) _figures[n].setPosition(pos.x-dx,pos.y-dy);
        
    }

    void GameState::update(float dt) {
        float x = 0;
        float y = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            x -= 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            x += 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            y -= 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            y += 2;
        }

        _board.move(x, y);
    }

    void GameState::render(float dt) {
#ifdef DEBUG
        std::stringstream ss;
        ss << "UPS: " << _data->UPS << " FPS: " << _data->FPS << " (approx.)";
        _stats.setString(ss.str());
#endif
        _data->window.clear(sf::Color::Red);
        _data->window.draw(_board);

        for (int i = 0; i < 32; ++i)
        {
            _figures[i].move(offset);
            _data->window.draw(_figures[i]);
            _figures[i].move(-offset);
        }
        _data->window.draw(_text);
#ifdef DEBUG
        _data->window.draw(_stats); // Show "UPS: # FPS: #"
#endif
        _data->window.display();
    }
}