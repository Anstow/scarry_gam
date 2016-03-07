#include "Node.hpp"

#include "../serial/node.pb.h"

#include <iostream>
#include <fstream>
#include <SFML/Graphics/Transform.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

Node::Node()
{
    tx_.loadFromFile("res/gfx/vert_00.png");
    sprite_.setTexture(tx_);
    tileSize_ = tx_.getSize();
    edgeCount_ = 0;
    serial::NodeMeta nodeData;
    {
        std::fstream input("../res/nodes/node1.tbuf", std::ios::in);
        google::protobuf::io::IstreamInputStream stream(&input);
        if (google::protobuf::TextFormat::Parse(&stream, &nodeData)) {
            // TODO: handle this a little more elegantly
            throw "Problem parsing file.";
        }
    }
    collision_ = std::make_unique<CollisionMap>(nodeData.boundaries());
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

CollisionMap* Node::getCollisionMap() {
    return collision_.get();
}

void Node::updateLayout()
{
    /* Fix graphics and match holes */
}
