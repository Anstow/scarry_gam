#include "Entity.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <memory>

#include "../input/InputInterface.hpp"

#include "Vector.hpp"
#include "Node.hpp"
#include "Collision.hpp"

class Player : public Entity
{
    static constexpr double minSpeed_ = 0.001;
    static constexpr double accel_ = 8.0;
    static constexpr double damping_ = 0.75;
    static constexpr double time_ = 0.25;
    static constexpr float radius_ = 20.0;
    // A positive value for restitution_ is needed to stop things getting stuck
    static constexpr float restitution_ = 0.01f;

    using Vertex = unsigned;
    std::unique_ptr<input::InputInterface const> controller_;
    sf::CircleShape sprite_ {radius_};
    Node* currentNode_;

    tank::Vectorf vel_{0,0};

public:
    Player(std::unique_ptr<input::InputInterface const> input, Node* startNode_);

    void update() override;
    void draw(sf::RenderTarget&) const override;

    void moveBy(tank::Vectorf const& force);

    Node* getCurrentNode() { return currentNode_; }

    void setPos(tank::Vectorf const&) override;

    tank::Vectorf getCentre();
    void setCentre(tank::Vectorf const& centre);

private:
    CollisionMap* getCollisionMap();
};
