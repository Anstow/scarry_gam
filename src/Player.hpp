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

    tank::Vectorf vel_{0,0};

    static constexpr double minSpeed_ = 0.001;
    static constexpr double accel_ = 8.0;
    static constexpr double damping_ = 0.75;
    static constexpr double time_ = 0.25;

public:
    Player(tank::Controller const& c, Vertex startNode_);

    void update() override;
    void draw(sf::RenderTarget&) const override;

    void moveBy(tank::Vectorf const& disp);
    
    Vertex const& getCurrentNode() const { return currentNode_; }
};
