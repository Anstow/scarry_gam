#ifndef INPUT_INTERFACE_HPP
#define INPUT_INTERFACE_HPP

#include <SFML/System/Vector2.hpp>

namespace input {

class InputInterface {
public:
    virtual sf::Vector2f getMovementDisp() const = 0;
};

}

#endif // INPUT_INTERFACE_HPP
