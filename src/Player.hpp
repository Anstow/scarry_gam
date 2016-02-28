#include "Entity.hpp"

#include <Tank/System/Controller.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "Vector.hpp"

class Player : public Entity
{
    using Vertex = unsigned;
    tank::Controller const& controller_;
    sf::CircleShape sprite_ {20};
    Vertex currentNode_;

    static constexpr double speed_ = 2;

public:
    Player(tank::Controller const& c, Vertex startNode_);

    void update() override;
    void draw(sf::RenderTarget&) const override;
    
    Vertex const& getCurrentNode() const { return currentNode_; }
};
