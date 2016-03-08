#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "../serial/node.pb.h"

#include <SFML/System/Vector2.hpp>

#include <vector>
#include <tuple>
#include <algorithm>

struct CollisionData {
    sf::Vector2f normal;

    float time;
};

struct Ball {
    sf::Vector2f centre;
    float radius;

    sf::Vector2f vel;
};

class CollisionMap {
    /*!
     * \brief The points to test for a collision against.
     */
    std::vector<std::vector<sf::Vector2f>> collisionLines_;

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
