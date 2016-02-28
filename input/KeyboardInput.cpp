#include "KeyboardInput.hpp"

#include <Tank/System/Keyboard.hpp>

using namespace input;

KeyboardInput::KeyboardInput()
{}

tank::Vectorf KeyboardInput::getMovementDisp() const {
    tank::Vectorf disp{0,0};

    if (tank::Keyboard::isKeyDown(tank::Key::Left)) {
        disp += tank::Vectorf{1,0};
    }
    if (tank::Keyboard::isKeyDown(tank::Key::Right)) {
        disp += tank::Vectorf{-1,0};
    }
    if (tank::Keyboard::isKeyDown(tank::Key::Up)) {
        disp += tank::Vectorf{0,-1};
    }
    if (tank::Keyboard::isKeyDown(tank::Key::Down)) {
        disp += tank::Vectorf{0,1};
    }

    // normalise
    if (disp.x != 0 and disp.y != 0) {
        disp /= std::sqrt(2);
    }

    return disp;
}
