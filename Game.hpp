#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "Board.hpp"

namespace Checkers {
    struct GameData {
        StateMachine machine;
        sf::RenderWindow window;
        AssetManager assets;
				InputManager input;
    };

    typedef std::shared_ptr<GameData> GameDataRef;

    class Game {
        public:
            Game(int width, int height, std::string title);

        private:
            // Updates run at 30 per second.
            const float dt = 1.0f / 30.0f;
            sf::Clock _clock;
            GameDataRef _data = std::make_shared<GameData>();

            void run();
    };
}

#endif // GAME_HPP
