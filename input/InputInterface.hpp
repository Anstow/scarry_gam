#ifndef INPUT_INTERFACE_HPP
#define INPUT_INTERFACE_HPP

#include <Tank/Utility/Vector.hpp>

namespace input {

class InputInterface {
public:
    virtual tank::Vectorf getMovementDisp() const = 0;
};

}

#endif // INPUT_INTERFACE_HPP
