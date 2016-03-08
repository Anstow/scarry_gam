#ifndef XBOX_CONTROLLER_INPUT_HPP
#define XBOX_CONTROLLER_INPUT_HPP

#include <Tank/System/Controller.hpp>

#include "InputInterface.hpp"

namespace input {

class ControllerInput : public InputInterface {
    static constexpr float dead_zone = 0.2; // inverse pad sensitivity [0,1]

    // TODO: This should be redundent
    tank::Controller const& controller_;

public:    
    ControllerInput(tank::Controller const& controller);

    virtual sf::Vector2f getMovementDisp() const override final;
};

}


#endif // XBOX_CONTROLLER_INPUT_HPP
