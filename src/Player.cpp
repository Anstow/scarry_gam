#include "Player.hpp"

#include <iostream>

constexpr double Player::minSpeed_;
constexpr double Player::accel_;
constexpr double Player::damping_;
constexpr double Player::time_;

Player::Player(tank::Controller const& c, Vertex vert_id)
    : controller_ {c}
    , currentNode_ {vert_id}
{
    auto& pos = getPos();
    sprite_.setPosition(pos.x, pos.y);
}

void Player::update()
{
    constexpr float dead_zone = 0.2; // inverse pad sensitivity [0,1]

    tank::Vectorf ls = controller_.leftStick();
    float magnitude = ls.magnitude();
    tank::Vectorf disp = {0,0};
    if (magnitude > dead_zone) {
        disp = ls - (dead_zone * (ls / magnitude)) / (1 - dead_zone);
    }
    moveBy(disp);
}

void Player::draw(sf::RenderTarget& target) const
{
    target.draw(sprite_);
}

void Player::moveBy(tank::Vectorf const& disp) {

    auto& pos = getPos();
    pos += vel_ * time_  + disp * accel_ * time_ * time_ / 2;
    vel_ *= damping_;
    vel_ += disp * accel_ * time_;

    sprite_.setPosition(pos.x, pos.y);
}
