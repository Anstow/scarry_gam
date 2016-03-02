#include "Collision.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

CollisionMap::CollisionMap(std::string file)
{
    sf::Image t;
    t.loadFromFile(file);

    auto size = t.getSize();
    auto collideColor = t.getPixel(0,0);

    for(unsigned int x = 0; x < size.x; ++x) {
        for(unsigned int y = 0; y < size.y; ++y) {
            if (t.getPixel(x,y) == collideColor and
                ((x != 0 and t.getPixel(x-1,y) != collideColor) or
                 (x != size.x - 1 and t.getPixel(x+1,y) != collideColor) or
                 (y != 0 and t.getPixel(x,y-1) != collideColor) or
                 (y != size.y - 1 and t.getPixel(x,y+1) != collideColor))) {
                testPoints_.push_back(tank::Vectorf{x,y});
            }
        }
    }
}

float collideBallWithPoint(
        Ball const& b,
        tank::Vectorf const& point,
        float time) {
    /* Let c = (c_1, c_2) be the centre of the ball, let r be its radius, let
     * v = (v_1, v_2) be its velocity, let p = (p_1, p_2) be the point
     * and let x = (x_1, x_2) be a general point.
     *
     * The equation for the ball is
     * |c - x|^2 = r^2
     * and the equation for the line of the point moving with velocity -v is
     * x = p - v t.
     *
     * Substituting that back in, the equation to be solved is:
     * |v t + c - p|^2 = r^2.
     * I.e.
     * A t^2 + B t + C = 0,
     * where
     * A = |v|^2,
     * B = 2 v . (c - p), and
     * C = |c - p|^2 - r^2.
     *
     * We are looking for the least positive solution to this where t < time.
     * If there is only one positive solution we may ingore it as this
     * corresponds to the case when the point is inside the ball.
     */
    float A = b.vel.magnitudeSquared();
    float B = 2 * (b.vel.dot(b.centre - point));
    float C = (b.centre - point).magnitudeSquared() - b.radius * b.radius;
    
    /* If velocity is small don't bother colliding.
     * If there is at most one positive solution we don't collide.
     * If there are no solutions.
     */
    if (A < 0.0000001f or
        B > 0 or
        B * B - 4 * A * C < 0) {
        return time;
    }

    return std::min(time, (-B - std::sqrt(B * B - 4 * A * C)) / (2 * A));
}

CollisionData CollisionMap::getBallCollision(
        Ball const& b,
        float time) {
    tank::Vectorf collidePoint = {0,0};
    std::for_each(testPoints_.begin(), testPoints_.end(), 
            [&](tank::Vectorf const& p) {
                float collisionTime = collideBallWithPoint(b, p, time);
                if (time > collisionTime) {
                    time = collisionTime;
                    collidePoint = p;
                }
            });
    return { collidePoint, time };
}
