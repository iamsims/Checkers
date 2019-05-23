#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

namespace Checkers {

    void AssetManager::loadTexture(std::string name, std::string fileName) {
        sf::Texture tex;
        if (tex.loadFromFile(fileName)) {
						tex.setRepeated(true);
            _textures[name] = tex;
        }
    }

    sf::Texture& AssetManager::getTexture(std::string name) {
        return _textures.at(name);
    }

    void AssetManager::loadFont(std::string name, std::string fileName) {
        sf::Font font;
        if (font.loadFromFile(fileName)) {
            _fonts[name] = font;
        }
    }

    sf::Font& AssetManager::getFont(std::string name) {
        return _fonts.at(name);
    }
}
