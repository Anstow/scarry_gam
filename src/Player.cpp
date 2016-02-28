#include "Player.hpp"

#include <iostream>

constexpr double Player::minSpeed_;
constexpr double Player::accel_;
constexpr double Player::damping_;
constexpr double Player::time_;

Player::Player(tank::Controller const& c, Node* node)
    : controller_ {c}
    , currentNode_ {node}
{
}

void Player::update()
{
    constexpr float dead_zone = 0.2; // inverse pad sensitivity [0,1]

    tank::Vectorf ls = controller_.leftStick();
    float magnitude = ls.magnitude();
    tank::Vectorf force = {0,0};
    if (magnitude > dead_zone) {
        force = ls - (dead_zone * (ls / magnitude)) / (1 - dead_zone);
    }
    moveBy(force);
}

void Player::draw(sf::RenderTarget& target) const
{
    target.draw(sprite_);
}

void Player::moveBy(tank::Vectorf const& force)
{
    auto pos = getPos();
    auto disp = vel_ * time_  + force * accel_ * time_ * time_ / 2;
    disp /= 600;
    pos += disp;
    vel_ *= damping_;
    vel_ += force * accel_ * time_;

    setPos(pos);
}

void Player::setPos(tank::Vectorf const& pos)
{
    Entity::setPos(pos);
    sprite_.setPosition(pos.x, pos.y);
}
