#include "Player.hpp"

#include "../sfml_extensions/VectorExtensions.hpp"

#include <iostream>

constexpr float Player::minSpeed_;
constexpr float Player::accel_;
constexpr float Player::damping_;
constexpr float Player::time_;
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

void Player::setPos(sf::Vector2f const& pos)
{
    Entity::setPos(pos);
    sprite_.setPosition(pos.x, pos.y);
}

void Player::moveBy(sf::Vector2f const& force) {
    // The position of the centre of the ball
    sf::Vector2f pos = getCentre();

    float timeInterval = time_;
    vel_ = vel_ * damping_ + force * accel_ * timeInterval;

    while (timeInterval > 0)
    {
        // Find any collision points
        auto collideData
            = getCollisionMap()->getBallCollision(Ball{pos, radius_, vel_}, timeInterval);
        timeInterval -= collideData.time;
        pos = pos + vel_ * collideData.time;

        // If there has been a collision, prepare for the next loop
        if (timeInterval > 0) {
            // The unit vector away form the point collided with
            float velParallelToNormal = dot(collideData.normal, vel_);
            /* Why does resititution + 1 work?
             * 1:            to cancel out all the motion towards the point
             *               collided with.
             * restitution_: to bounce back from the collided point
             **/
            vel_ -= collideData.normal * ((1 + restitution_) * velParallelToNormal);
        }
    }
    setCentre(pos);
}


sf::Vector2f Player::getCentre() {
    return getPos() + sf::Vector2f{radius_, radius_};
}

void Player::setCentre(sf::Vector2f const& centre) {
    setPos(centre - sf::Vector2f{radius_, radius_});
}

CollisionMap* Player::getCollisionMap() {
    return currentNode_->getCollisionMap();
}
