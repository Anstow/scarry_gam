#include "Player.hpp"

#include <iostream>

constexpr double Player::minSpeed_;
constexpr double Player::accel_;
constexpr double Player::damping_;
constexpr double Player::time_;

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

void Player::moveBy(tank::Vectorf const& force)
{
    auto pos = getPos();
    auto disp = vel_ * time_  + force * accel_ * time_ * time_ / 2;
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
