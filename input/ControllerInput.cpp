#include "ControllerInput.hpp"

#include "../sfml_extensions/VectorExtensions.hpp"

using namespace input;

constexpr float ControllerInput::dead_zone;

ControllerInput::ControllerInput(tank::Controller const& controller)
    : controller_(controller)
{}

sf::Vector2f ControllerInput::getMovementDisp() const {
    sf::Vector2f ls = sf::vector_cast<float>(controller_.leftStick());
    float mag = sf::magnitude(ls);

    sf::Vector2f force = {0,0};
    if (mag > dead_zone) {
        force = ls - (dead_zone * (ls / mag)) / (1 - dead_zone);
    }
    return force;
}
