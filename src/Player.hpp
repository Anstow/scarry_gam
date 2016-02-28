#include "Entity.hpp"

#include <Tank/System/Controller.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "Vector.hpp"
#include "Node.hpp"

class Player : public Entity
{
    tank::Controller const& controller_;
    sf::CircleShape sprite_ {20};
    Node* currentNode_;

    tank::Vectorf vel_{0,0};

    static constexpr double minSpeed_ = 0.001;
    static constexpr double accel_ = 8.0;
    static constexpr double damping_ = 0.75;
    static constexpr double time_ = 0.25;

public:
    Player(tank::Controller const& c, Node* startNode_);

    void update() override;
    void draw(sf::RenderTarget&) const override;

    void moveBy(tank::Vectorf const& force);

    Node* getCurrentNode() { return currentNode_; }

    void setPos(tank::Vectorf const&) override;
};
