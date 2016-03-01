#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "Vector.hpp"

class Entity
{
    Vec pos_ {0, 0};

public:
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget&) const = 0;

    Vec const& getPos() const { return pos_; } 
    virtual void setPos(Vec const& p) {  pos_ = p; } 

};
