#include "Entity.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <memory>

#include "../input/InputInterface.hpp"

#include "Vector.hpp"
#include "Node.hpp"
#include "Collision.hpp"

class Player : public Entity
{
    static constexpr float minSpeed_ = 0.001f;
    static constexpr float accel_ = 8.0f;
    static constexpr float damping_ = 0.75f;
    static constexpr float time_ = 0.25f;
    static constexpr float radius_ = 20.0f;
    // A positive value for restitution_ is needed to stop things getting stuck
    static constexpr float restitution_ = 0.01f;

    using Vertex = unsigned;
    std::unique_ptr<input::InputInterface const> controller_;
    sf::CircleShape sprite_ {radius_};
    Node* currentNode_;

    sf::Vector2f vel_{0,0};

public:
    Player(std::unique_ptr<input::InputInterface const> input, Node* startNode_);

    void update() override;
    void draw(sf::RenderTarget&) const override;

    void moveBy(sf::Vector2f const& force);

    Node* getCurrentNode() { return currentNode_; }

    void setPos(sf::Vector2f const&) override;

    sf::Vector2f getCentre();
    void setCentre(sf::Vector2f const& centre);

private:
    CollisionMap* getCollisionMap();
};
