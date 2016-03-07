#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "../serial/node.pb.h"

#include <vector>
#include <tuple>
#include <Tank/Utility/Vector.hpp>
#include <algorithm>

struct CollisionData {
    tank::Vectorf normal;

    float time;
};

struct Ball {
    tank::Vectorf centre;
    float radius;

    tank::Vectorf vel;
};

class CollisionMap {
    /*!
     * \brief The points to test for a collision against.
     */
    std::vector<std::vector<tank::Vectorf>> collisionLines_;

public:
    unsigned width;
    unsigned height;

    CollisionMap(serial::Boundary const& boundary);

    /*!
     * \brief This get the collision data for the ball.
     *
     * \param b the ball to collide with.
     * \param vel The velocity of the ball.
     * \param time The time interval to collide over
     *
     * \return A struct contianing the point collided with and the time the collision occured
     */
    CollisionData getBallCollision(
            Ball const& b,
            float time);
};

#endif // COLLISION_HPP
