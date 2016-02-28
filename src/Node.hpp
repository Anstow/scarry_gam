#pragma once

#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Entity.hpp"

class Node : public Entity
{
    sf::Texture tx_;
    sf::Sprite sprite_;
    std::vector<std::unique_ptr<Entity>> entities_;

    unsigned edgeCount_;

public:
    Node();

    unsigned edgeCount() const { return edgeCount_; }

    void updateEdgeCount(unsigned edges);

    void addEntity(std::unique_ptr<Entity>&&);

    void update() override;
    void draw(sf::RenderTarget&) const override;

private:

    void updateLayout();
};
