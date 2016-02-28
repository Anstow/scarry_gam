#include "ControllerInput.hpp"

using namespace input;

constexpr float ControllerInput::dead_zone;

ControllerInput::ControllerInput(tank::Controller const& controller)
    : controller_(controller)
{}

tank::Vectorf ControllerInput::getMovementDisp() const {
    tank::Vectorf ls = controller_.leftStick();
    float magnitude = ls.magnitude();

    tank::Vectorf force = {0,0};
    if (magnitude > dead_zone) {
        force = ls - (dead_zone * (ls / magnitude)) / (1 - dead_zone);
    }
    return force;
}
