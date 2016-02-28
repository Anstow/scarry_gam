#include "KeyboardInput.hpp"

#include <Tank/Utility/Vector.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace input;

KeyboardInput::KeyboardInput()
{}

tank::Vectorf KeyboardInput::getMovementDisp() const {
    tank::Vectorf disp{0,0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        disp += tank::Vectorf{1,0};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        disp += tank::Vectorf{-1,0};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        disp += tank::Vectorf{0,-1};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        disp += tank::Vectorf{0,1};
    }

    // normalise
    if (disp.x != 0 and disp.y != 0) {
        disp /= std::sqrt(2); // We know we must be travelling diagonally!
    }

    return disp;
}
