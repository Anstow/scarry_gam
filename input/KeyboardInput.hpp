#ifndef KEYBOARD_INPUT_HPP
#define KEYBOARD_INPUT_HPP

#include "InputInterface.hpp"

namespace input {

class KeyboardInput : public InputInterface {
public:
    KeyboardInput();

    virtual tank::Vectorf getMovementDisp() const override final;
};

}

#endif // KEYBOARD_INPUT_HPP
