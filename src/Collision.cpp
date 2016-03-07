#include "Collision.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

struct Circle {
    tank::Vectorf centre;
    float radius;
};

struct LineSegment {
    tank::Vectorf e1;
    tank::Vectorf e2;
};

struct PointMovement {
    tank::Vectorf pos;
    tank::Vectorf vel;
};

CollisionMap::CollisionMap(serial::Boundary const& boundaries) {
    auto bs = boundaries.line_list_size();
    serial::LineList lineList;
    serial::Point pt;
    for (int i = 0; i < bs; ++i) {
        lineList = boundaries.line_list(i);
        auto ls = lineList.points_size();
        collisionLines_.push_back(std::vector<tank::Vectorf>());
        auto& cl = collisionLines_.back();
        for (int j = 0; j < ls; ++j) {
            pt = lineList.points(j);
            cl.emplace_back(pt.x(), pt.y());
        }
    }
}

/*
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
*/

CollisionData collideWithCircle(
        PointMovement const& p,
        Circle const& c,
        float time) {
    /* Let c be the centre of the circle, and let r be its radius. Then then
     * equation for the circle is
     * |x - c|^2 = r^2
     * 
     * Let v be the velocity of the point, and let p be the position of the
     * point. Then the position of the point after time t is
     * x = p + v t.
     *
     * Substituting that back in, the equation to be solved is:
     * |v t + p - c|^2 = r^2.
     * I.e.
     * A t^2 + B t + C = 0,
     * where
     * A = |v|^2,
     * B = 2 v . (p - c), and
     * C = |p - c|^2 - r^2.
     *
     * We are looking for the least positive solution to this where t < time.
     * If there is only one positive solution we may ingore it as this
     * corresponds to the case when the point is inside the ball.
     */
    float A = p.vel.magnitudeSquared();
    float B = 2 * (p.vel.dot(p.pos - c.centre));
    float C = (p.pos - c.centre).magnitudeSquared() - c.radius * c.radius;
    
    /* If velocity is 0 don't collide with this algorithm
     * If there is at most one positive solution we don't collide.
     * If there are no solutions.
     */
    if (A <= 0 or
        B > 0 or
        B * B - 4 * A * C < 0) {
        return {{0,0}, time};
    }
    float t = (-B - std::sqrt(B * B - 4 * A * C)) / (2 * A);
    return { (c.centre - (p.pos + p.vel * t)).unit(), std::min(time, t) };
}

CollisionData collideWithOffsetLine(
        PointMovement const& p,
        LineSegment const& l,
        float offset,
        float time) {
    /* Let e1, e2 be the end points of the line. Then the equation for the
     * line is. When u is the unit normal.
     * x = e1 + s (e2 - e1) + u offset
     * for a variable s.
     *
     * Let v be the velocity of the point, let p be the position of the point,
     * then the position of the point after time t is
     * x = p + t v
     *
     * Substituting that back in, the equation to be solved is:
     * e1 - p = t v + s (e1 - e2)
     *        = | e1-e2   v | |s|
     *                        |t|
     * Let d = e1 - p - u offset and let n be the normal to the line e1, e2. Then 
     * n = |  (e2-e1)_y |
     *     | -(e2-e1)_x |
     * det = (e1-e2)_x v_y - (e1-e2)_y v_x 
     *     = n . v
     *
     * We only collide if we a travelling towards to line i.e.
     * det < 0
     *
     * s = (v_y d_x - v_x d_y) / det
     *
     * We only collide if 
     * s >= 0 and s <= 1
     * i.e. as det < 0 if
     * s det <= 0 and s det >= det
     *
     * Then
     * t = ((e2-e1)_y d_x - (e2-e1)_x z_y) / det
     *   = n . d / det
     * 
     * Only collide when t >= 0
     * i.e. if
     * t det <= 0
     */
    tank::Vectorf normal{ (l.e2 - l.e1).y, -(l.e2 - l.e1).x };
    tank::Vectorf unit_normal = normal.unit();
    tank::Vectorf diff = l.e1 - p.pos + unit_normal * offset;
    float det = normal.dot(p.vel);
    // Check we are moving towards the line
    if (det >= 0)
        return { {0,0}, time };
    float sdet = p.vel.y * diff.x  - p.vel.x * diff.y;
    // We missed the line segment
    if (sdet > 0 or sdet < det)
        return { {0,0}, time };
    float tdet = normal.dot(diff);
    if (tdet > 0)
        return { {0,0}, time };
    return { unit_normal, tdet / det };
}

CollisionData collideWithLineList(
        PointMovement const& p,
        std::vector<tank::Vectorf> const& ll,
        float const radius,
        float const time) {
    auto minCollisionPoint = 
            [](CollisionData const& c1, CollisionData const& c2) {
                if (c1.time <= c2.time)
                    return c1;
                else
                    return c2;
            };
    CollisionData cd = {{0,0}, time};
    // Avoid trying to collide when there is nothing to collide with
    if (ll.empty()) {
        return cd;
    }
    // Abuse of accumulate to iterate through the points.
    cd = std::accumulate(ll.begin(), ll.end(), cd,
            [=](CollisionData const& c1, tank::Vectorf const& point) {
                return minCollisionPoint(c1, collideWithCircle(p, {point, radius}, time));
            });
    // Abuse of inner product to iterate over pairs of points!
    cd = std::inner_product(ll.begin() + 1, ll.end(), ll.begin(), cd,
            minCollisionPoint,
            [=](tank::Vectorf const& e1, tank::Vectorf const& e2) {
                if (e1 == e2) {
                    return CollisionData{{0,0}, time};
                } else {
                    return collideWithOffsetLine(p, {e1, e2}, radius, time);
                }
            });
    return cd;
}

CollisionData CollisionMap::getBallCollision(
        Ball const& b,
        float time) {
    CollisionData ret = {{0,0}, time};
    std::for_each(collisionLines_.begin(), collisionLines_.end(), 
            [&](std::vector<tank::Vectorf> const& cl) {
                auto cd = collideWithLineList({b.centre, b.vel}, cl, b.radius, time);
                if (time > cd.time) {
                    ret = cd;
                }
            });
    return ret;
}
