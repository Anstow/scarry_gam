#include "Player.hpp"

#include <iostream>

constexpr double Player::minSpeed_;
constexpr double Player::accel_;
constexpr double Player::damping_;
constexpr double Player::time_;
constexpr float Player::radius_;

Player::Player(std::unique_ptr<input::InputInterface const>&& input, Node* node)
    : controller_ {std::move(input)}
    , currentNode_ {node}
{
}

void Player::update()
{
    // Input
    moveBy(controller_->getMovementDisp());
}

void Player::draw(sf::RenderTarget& target) const
{
    target.draw(sprite_);
}

void Player::setPos(tank::Vectorf const& pos)
{
    Entity::setPos(pos);
    sprite_.setPosition(pos.x, pos.y);
}

tank::Vectorf averageVector(const std::vector<Point>& toAverage) {
    if (toAverage.size() == 0)
    {
        // We shouldn't average something with no members
        return {0.0f, 0.0f};
    }

    // Find sum and divide by number to get average
    tank::Vectorf sum{0.0f, 0.0f};
    for (auto point : toAverage)
    {
        sum += tank::Vectorf{static_cast<float>(point.x),
                             static_cast<float>(point.y)};
    }
    return sum / toAverage.size();
}

void Player::moveBy(tank::Vectorf const& disp) {

    float timeInterval = time_;

    // The position of the centre of the ball
    tank::Vectorf pos = getCentre();
    // The change in the position of the ball based on newtons laws assuming no
    // collision
    tank::Vectorf dPos = vel_ * timeInterval;
    dPos += accel_ * (0.5 * timeInterval * timeInterval);
    while (timeInterval > 0)
    {
        // Find any collision points
        auto collisionData
            = getCollisionMap()->getBallCollisionPoints(pos, radius_, dPos);

        if (collisionData.points.size() == 0)
        {
            // There was no collision - just move ball
            vel_ *= damping_;
            vel_ += disp * accel_ * time_;
            vel_ += accel_ * timeInterval;

            setCentre(pos + dPos);
            timeInterval = 0;
        }
        else
        {
            // There was a collision.

            // Get the time until the instant before the collision
            float timeBeforeCollision
                   = (collisionData.time - collisionData.time_interval) * timeInterval;

            // We want to set the position, velocity and time to the instant
            // before the collision
            pos += dPos * timeBeforeCollision;
            // Set the velocity based on newtons laws
            vel_ += accel_ * timeBeforeCollision;
            // make the timeInterval smaller
            timeInterval -= timeBeforeCollision;

            // Calculate the collision normal from the average direction from the
            // circle's centre to each collision pixel
            tank::Vectorf collisionNormal =
                   (pos - averageVector(collisionData.points)).unit();
            // Calculate the component of the velocity in the direction normal
            // to the surface collided with
            float velParallelToNormal = collisionNormal.dot(vel_);
            // Why does resititution + 1 work?
            // Why no horizontal? We only need to deal with the motion normal
            // to the plane
            vel_ -= collisionNormal * ((1 + restitution_) * velParallelToNormal);
            dPos = vel_;
            // OK this vector class is getting ridiculous
            dPos *= timeInterval;
            dPos += accel_ * (0.5 * timeInterval * timeInterval);

            if (timeBeforeCollision == 0 && velParallelToNormal < 0.05)
            {
                // corner case: rolling 
                if (vel_.magnitudeSquared() < 0.001)
                {
                    // Finished moving
                    timeInterval = 0;
                }
                else
                {
                    // Hack to try to make it work, it appears it does now
                    pos += collisionNormal * 0.02;
                }
            }
        }
    }
    setCentre(pos);
}


tank::Vectorf Player::getCentre() {
    return getPos() - tank::Vectorf{radius_, radius_};
}

void Player::setCentre(tank::Vectorf const& centre) {
    setPos(centre + tank::Vectorf{radius_, radius_});
}

CollisionMap* Player::getCollisionMap() {
    return currentNode_->getCollisionMap();
}
