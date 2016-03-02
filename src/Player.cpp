#include "Player.hpp"

#include <iostream>

constexpr double Player::minSpeed_;
constexpr double Player::accel_;
constexpr double Player::damping_;
constexpr double Player::time_;
constexpr float Player::radius_;

Player::Player(std::unique_ptr<input::InputInterface const> input, Node* node)
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

void Player::moveBy(tank::Vectorf const& force) {
    // The position of the centre of the ball
    tank::Vectorf pos = getCentre();

    float timeInterval = time_;
    tank::Vectorf vel = vel_ * damping_ + force * accel_ * timeInterval;

    /* TODO: There is a weird jittering when running into walls head on, this
     * is because we are modelling walls as a collection of pixels and on
     * collision we rapidly swap between coliding with 2 different pixels. 
     *
     * This shouldn't be noticeable with the controller as I believe there will
     * almost always be a slight glide one way or the other.
     *
     * Fix: When line collisions are implemented this shouldn't happen any
     * more.
     */
    while (timeInterval > 0)
    {
        // Find any collision points
        auto collideData
            = getCollisionMap()->getBallCollision(Ball{pos, radius_, vel_}, timeInterval);
        timeInterval -= collideData.time;
        pos = pos + vel_ * collideData.time;
        vel_ = vel_ * damping_ + force * accel_ * collideData.time;

        // If there has been a collision, prepare for the next loop
        if (timeInterval > 0) {
            // The unit vector away form the point collided with
            tank::Vectorf collisionNormal = (pos - collideData.point).unit();
            float velParallelToNormal = collisionNormal.dot(vel_);
            // Why does resititution + 1 work?
            // 1:            to cancel out all the motion towards the point
            //               collided with.
            // restitution_: to bounce back from the collided point
            vel_ -= collisionNormal * ((1 + restitution_) * velParallelToNormal);
            
            // The new velocity
            vel = vel_ + force * accel_ * timeInterval;

            // If we aren't stepping very far and we are accelerating towards
            // the collided point break out of the loop.
            if (collideData.time < 0.0001f and
                collisionNormal.dot(accel_) < 0) {
                break;
            }
        }
    }
    setCentre(pos);
}


tank::Vectorf Player::getCentre() {
    return getPos() + tank::Vectorf{radius_, radius_};
}

void Player::setCentre(tank::Vectorf const& centre) {
    setPos(centre - tank::Vectorf{radius_, radius_});
}

CollisionMap* Player::getCollisionMap() {
    return currentNode_->getCollisionMap();
}
