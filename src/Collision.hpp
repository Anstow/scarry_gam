#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <vector>
#include <tuple>
#include <Tank/Utility/Vector.hpp>
#include <algorithm>

struct Point {
    int x, y;
};

struct CollisionData {
    std::vector<Point> points;

    float time;
    float time_interval;
};

class CollisionMap {
    std::vector<bool> collide_;

public:
    unsigned width;
    unsigned height;

    CollisionMap(std::string fileName);

    /*!
     * \brief This loads the collision data and sets the background image
     * correspondingly.
     *
     * \param fileName The name of the file with the bitmap data in.
     */
    void load(std::string fileName);

    /*!
     * \brief This get the collision data for the ball.
     *
     * \param centre The centre of the ball to collide with the map
     * \param radius The radius of the ball to collide with the map
     * \param dPos The change in the centre of the ball.
     *
     * \return A tuple consisting of
     * - The vector of the points at which there is a collision
     * - The time at which the colision occurs
     * - The time intreval used in calculating the collision data
     */
    CollisionData getBallCollisionPoints(
            const tank::Vectorf& centre,
            float radius,
            const tank::Vectorf& dPos);

    bool collideAt(unsigned x, unsigned y);
};

#endif // COLLISION_HPP
