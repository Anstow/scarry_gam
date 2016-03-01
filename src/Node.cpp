#include "Node.hpp"

#include <iostream>
#include <SFML/Graphics/Transform.hpp>

Node::Node()
{
    tx_.loadFromFile("res/gfx/vert_00.png");
    sprite_.setTexture(tx_);
    tileSize_ = tx_.getSize();
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

    for (auto& e : entities_)
    {
        // I don't know what the commented out lines are for?
        //auto old_pos = e->getPos();
        //e->setPos({old_pos.x*tileSize_.x, old_pos.y*tileSize_.y});
        e->draw(target);
        //e->setPos(old_pos);
        //std::cout << old_pos.x*tileSize_.x << "\n";
    }
}

void Node::updateLayout()
{
    /* Fix graphics and match holes */
}
