#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <algorithm>
#include <random>

#include "../graphs/graph.hpp"

namespace drawing {

constexpr float stepTime = 0.01f;

class Node {
    sf::CircleShape graphic_;
    sf::Vector2f vel_ = {0,0};

public:
    unsigned id;

    sf::Vector2f force = {0,0};

    Node(unsigned i, sf::Vector2f const& pos);

    void setPos(sf::Vector2f p);

    void setColor(sf::Color const& c);

    sf::Vector2f getPos() const;

    void draw(sf::RenderWindow& win) const;

    void stepSim(float time);
};


class Graph {
    using NodeItr = std::vector<Node>::iterator;
    using EdgeItr = std::vector<std::tuple<size_t, size_t, size_t>>::iterator;

    graphs::MapGraph g_;

    std::vector<Node> nodes_;
    using Edge = std::tuple<size_t, size_t, size_t>;
    // Tupple of node_ pos, node_ pos, edge id
    std::vector<Edge> edges_;

    NodeItr selected_ = nodes_.end();
    sf::Vector2f offset_ = {0,0};

    sf::Vector2f createPos_;

public:
    Graph(sf::Vector2f const& createPos);

    void clickHold(sf::Vector2f const& pos);

    void clickRelease(sf::Vector2f const& pos);
    
    void mouseMoved(sf::Vector2f const& pos);

    void draw(sf::RenderWindow& win);

    NodeItr selectAt(sf::Vector2f const& p);

    NodeItr getNodeFromId(unsigned id);

    void loadFromGraph();


    sf::Vector2f calcNodeForces(Node& v);

    void stepPhysics(float time = stepTime);
};

}

#endif // NODE_HPP
