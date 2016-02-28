#include "Node.hpp"

#include <iostream>

Node::Node()
{
    tx_.loadFromFile("res/gfx/vert_00.png");
    sprite_.setTexture(tx_);
    edgeCount_ = 0;
}

void Node::addEntity(std::unique_ptr<Entity>&& e) {
    entities_.emplace_back(std::move(e));
}

void Node::updateEdgeCount(unsigned edges)
{
    if (edgeCount_ == edges)
    {
        edgeCount_ = edges;
        updateLayout();
    }
}

void Node::update()
{
    for (auto& e : entities_)
    {
        e->update();
    }
}

void Node::draw(sf::RenderTarget& target) const
{
    target.draw(sprite_);

    for (auto const& e : entities_)
    {
        e->draw(target);
    }
}

void Node::updateLayout()
{
    /* Fix graphics and match holes */
}