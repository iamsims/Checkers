#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include <SFML/Graphics/Text.hpp>
#include "State.hpp"
#include "Game.hpp"


namespace Checkers {
    class PauseState : public State {
        public:
            PauseState(GameDataRef data);

            void init();

            // Again, no pause() or resume() methods.
            // This state only exists to demonstrate a state transition.

            void handleInput();
            void update(float dt) { } // Nothing to do here.
            void render(float dt);

        private:
            GameDataRef _data;

            sf::Text _text;
    };
}

#endif // PAUSE_STATE_HPP
