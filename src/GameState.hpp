#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"


namespace Checkers {
    class GameState : public State {
        public:
            GameState(GameDataRef data);

            void init();

            // No pause() or resume() methods here as this
            // is a very simple example of a game state.

            void handleInput();
            void update(float dt);
            void render(float dt);
            std::string moveNote(sf::Vector2f );

        private:
            GameDataRef _data;

            sf::Sprite _board;
            sf::Sprite _figures[32];
            sf::Vector2f offset = sf::Vector2f(28, 28);
            std::string position="";
            sf::Text _text;

            bool isMove=false;
            float dx=0, dy=0;
            sf::Vector2f oldPos,newPos;
            std::string str;
            int n=0; 

#ifdef DEBUG
            sf::Text _stats;
#endif
    };
}

#endif // GAME_STATE_HPP
