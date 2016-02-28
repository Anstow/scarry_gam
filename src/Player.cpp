#include "Player.hpp"

#include <iostream>

constexpr double Player::speed_;
Player::Player(tank::Controller const& c, Vertex vert_id)
    : controller_ {c}
    , currentNode_ {vert_id}
{
}

void Player::update()
{
    constexpr float dead_zone = 0.2; // inverse pad sensitivity [0,1]

    auto& pos = getPos();

    tank::Vectorf ls = controller_.leftStick();
    float magnitude = ls.magnitude();
    if (magnitude > dead_zone) {
        const auto disp = ls - (dead_zone * (ls / magnitude)) / (1 - dead_zone);

        pos += speed_ * disp;
    }

    sprite_.setPosition(pos.x, pos.y);
}

void Player::draw(sf::RenderTarget& target) const
{
    target.draw(sprite_);
}
