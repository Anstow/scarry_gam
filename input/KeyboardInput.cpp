#include "KeyboardInput.hpp"

#include <Tank/Utility/Vector.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace input;

KeyboardInput::KeyboardInput()
{}

sf::Vector2f KeyboardInput::getMovementDisp() const {
    sf::Vector2f disp{0,0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        disp += sf::Vector2f{-1,0};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        disp += sf::Vector2f{1,0};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        disp += sf::Vector2f{0,-1};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        disp += sf::Vector2f{0,1};
    }

    // normalise
    if (disp.x != 0 and disp.y != 0) {
        disp = disp / std::sqrt(2.0f); // We know we must be travelling diagonally!
    }

    return disp;
}
