#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <algorithm>
#include <random>

#include "../graphs/graph.hpp"

namespace drawing {

constexpr float springLength = 100.0f;
constexpr float defaultSpringDef = 400.0f;

constexpr float springConstEdge = 500.0f;
constexpr float gravity = 0.05f;
constexpr float nodeMass = 1.0f;
constexpr float damping = 0.85;
constexpr float stepTime = 0.01f;

constexpr float vectorLength(sf::Vector2f const& v) {
    return v.x * v.x + v.y * v.y;
}

class Node {
    sf::CircleShape graphic_;
    sf::Vector2f vel = {0,0};

public:
    unsigned id;

    sf::Vector2f force;

    Node(unsigned i, sf::Vector2f const& pos)
        : id(i) {
        graphic_.setPosition(pos);
        graphic_.setRadius(10.0f);
        graphic_.setFillColor({0,0,0,0});
        graphic_.setOutlineThickness(2.0f);
        graphic_.setOutlineColor({255,255,255});
    }

    void setPos(sf::Vector2f p) {
        graphic_.setPosition(p - sf::Vector2f{10.0f, 10.0f});
    }

    void setColor(sf::Color const& c) {
        graphic_.setOutlineColor(c);
    }

    sf::Vector2f getPos() const {
        return graphic_.getPosition() + sf::Vector2f{10.0f, 10.0f};
    }

    void draw(sf::RenderWindow& win) const {
        win.draw(graphic_);
    }

    void stepSim(float time) {
        vel *= damping;
        vel += time * force / nodeMass;

        setPos(getPos() + vel * time);
    }
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

    std::minstd_rand gen_{100};

    float getRandom() {
        return std::generate_canonical<float, 10>(gen_) * 2 - 1;
    }

public:
    Graph(sf::Vector2f const& createPos)
        : createPos_(createPos)
    {
        loadFromGraph();
    }

    void clickHold(sf::Vector2f const& pos) {
        selected_ = selectAt(pos);
        if (selected_ != nodes_.end()) {
            offset_ = selected_->getPos() - pos;
        }
    }

    void clickRelease(sf::Vector2f const& pos) {
        auto selected = selectAt(pos);
        if (selected != nodes_.end()) {
            g_.process(selected->id);
            loadFromGraph();
        }
    }
    
    void mouseMoved(sf::Vector2f const& pos) {
        if (selected_ != nodes_.end()) {
            selected_->setPos(pos + offset_);
        }
    }

    void draw(sf::RenderWindow& win) {
        std::for_each(nodes_.begin(), nodes_.end(),
                [&](Node const& n) {
                    n.draw(win);
                });
        std::for_each(edges_.begin(), edges_.end(),
                [&](Edge const& e) {
                    std::array<sf::Vertex, 2> vertices{{ nodes_[std::get<0>(e)].getPos(), nodes_[std::get<1>(e)].getPos() }};
                    win.draw(vertices.data(), vertices.size(), sf::PrimitiveType::LinesStrip);
                });
    }

    NodeItr selectAt(sf::Vector2f const& p) {
        return std::find_if(nodes_.begin(), nodes_.end(),
                [&](Node const& n) {
                    auto d = (n.getPos() - p);
                    return (d.x * d.x + d.y * d.y) < 100.0f;
                });
    }

    NodeItr getNodeFromId(unsigned id) {
        return std::find_if(nodes_.begin(), nodes_.end(),
                [=](Node const& n) {
                    return n.id == id;
                }); 
    }

    void loadFromGraph() {
        std::for_each(g_.vertexBegin(), g_.vertexEnd(),
                [this](graphs::Vertex& v) {
                    auto existingNode =
                        std::find_if(nodes_.begin(), nodes_.end(), [&](Node const& n) {
                                    return n.id == v.id;
                                });
                    if (existingNode == nodes_.end()) {
                        nodes_.push_back(Node{v.id, createPos_});
                    } else if (v.gen_info.processed) {
                        existingNode->setColor({255,0,0});
                    }
                });
        edges_.clear();
        std::for_each(g_.edgeBegin(), g_.edgeEnd(),
                [this](graphs::Edge const& e) {
                    // Find the position in the node graph of the first vertex
                    // associated to the edge
                    auto node1 = getNodeFromId(e.v1) - nodes_.begin(); 
                    // Find the position in the node graph of the second vertex
                    // associated to the edge
                    auto node2 = getNodeFromId(e.v2) - nodes_.begin(); 
                    edges_.push_back(std::make_tuple(node1, node2, e.id));
                });
        selected_ = nodes_.end();
    }

    float calcSpringForceMag(float len, float springConst) {
        // Expects len > 0
        return springConst * (len - springLength);
    }

    float calcGenForce(float lenSq) {
        return gravity / lenSq - defaultSpringDef * (1);
    }

    /*!
     * \brief Calculates the force of vertex 1 on vertex 2
     */
    sf::Vector2f calcEdgeForce(Node& v1, Node const& v2) {
        // We don't want the length of the edge to be 0 so move the vertex a little
        while (vectorLength(v2.getPos() - v1.getPos()) < 0.001f)
            v1.setPos(v1.getPos() + sf::Vector2f{getRandom(),getRandom()});
        sf::Vector2f offset = v2.getPos() - v1.getPos();
        float l = vectorLength(offset);
        return calcSpringForceMag(std::sqrt(l), springConstEdge) * offset / std::sqrt(l);
    }

    /*!
     * \brief Calculates the force of gravity vertex 1 on vertex 2
     */
    sf::Vector2f calcSingleNodeForce(Node& v1, Node const& v2) {
        // Don't act on yourself
        if (v1.id == v2.id)
            return {0,0};
        // We don't want the length of the edge to be 0 so move the vertex a little
        while (vectorLength(v2.getPos() - v1.getPos()) < 0.001f)
            v1.setPos(v1.getPos() + sf::Vector2f{getRandom(),getRandom()});
        sf::Vector2f offset = v2.getPos() - v1.getPos();
        float l = vectorLength(offset);
        return calcGenForce(l) * offset / std::sqrt(l);
    }

    sf::Vector2f calcNodeForces(Node& v) {
        sf::Vector2f force = sf::Vector2f{0,0};
        std::for_each(nodes_.begin(), nodes_.end(),
                [this, &v, &force](Node& v2) {
                    force += calcSingleNodeForce(v, v2);
                });
        return force;
    }

    void stepPhysics(float time = stepTime) {
        // Calculates the gravity forces on each node
        std::for_each(nodes_.begin(), nodes_.end(),
                [=](Node& v) {
                    v.force = calcNodeForces(v);
                });
        // Calulates the spring forces on each node
        std::for_each(edges_.begin(), edges_.end(),
                [=](Edge const& e) {
                    auto forceVec = calcEdgeForce(nodes_[std::get<0>(e)], nodes_[std::get<1>(e)]);

                    nodes_[std::get<0>(e)].force += forceVec;
                    nodes_[std::get<1>(e)].force -= forceVec;
                });
        // Step the simulation
        std::for_each(nodes_.begin(), nodes_.end(),
                [=](Node& n) {
                    n.stepSim(time);
                });
    }
};

}

#endif // NODE_HPP
