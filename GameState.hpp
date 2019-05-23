#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Board.hpp"

namespace Checkers {
    class GameState : public State {
        public:
            GameState(GameDataRef data, int mode);
            void init();
            void handleInput();
            void update(float dt);
            void render(float dt);
            void initPosition();

        private:
            Board* _mboard;
            GameDataRef _data;
            void initStats(sf::Text&, int, int);
            sf::Sprite _board, _figures[24], _outerBoard;
            sf::Vector2f offset = sf::Vector2f(28, 28);
            sf::Text _text, _wcount, _bcount, _gameover,_savegame;
            sf::RectangleShape rectangle;

            int bcount=0, wcount=0;
            bool moving=false;
            float dx=0, dy=0;
            int temp=24;
            sf::Vector2f currentPosition, newPos;
            std::string str;
            int _selectedPieceIndex;
            int gamemode;
            int savemode=0;
						void showGameOver();
						void checkConditionall();
    };
}
#endif
