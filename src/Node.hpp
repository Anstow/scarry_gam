#pragma once

#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Entity.hpp"

class Node : public Entity
{
public:
    using NodeID = unsigned;

private:
    sf::Texture tx_;
    sf::Sprite sprite_;
    std::vector<std::unique_ptr<Entity>> entities_;
    sf::Vector2u tileSize_;
    //const NodeID id_;
    NodeID id_;

    unsigned edgeCount_;

public:
    Node();

    NodeID getID() const { return id_; }
    void setID(NodeID id) { id_ = id; }

    unsigned edgeCount() const { return edgeCount_; }

    void updateEdgeCount(unsigned edges);

    void addEntity(std::unique_ptr<Entity>&&);

    void update() override;
    void draw(sf::RenderTarget&) const override;

private:

    void updateLayout();
};
