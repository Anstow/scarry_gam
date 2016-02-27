#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <algorithm>

#include "../graphs/graph.hpp"

namespace drawing {

class Node {
    sf::CircleShape graphic_;

public:
    graphs::Vertex& vert;

    Node(graphs::Vertex& v, sf::Vector2f const& pos)
        : vert(v) {
        graphic_.setPosition(pos);
        graphic_.setRadius(10.0f);
        graphic_.setFillColor({0,0,0,0});
        graphic_.setOutlineThickness(2.0f);
        graphic_.setOutlineColor({255,255,255});
    }

    void setPos(sf::Vector2f p) {
        graphic_.setPosition(p - sf::Vector2f{10.0f, 10.0f});
    }

    sf::Vector2f getPos() const {
        return graphic_.getPosition() + sf::Vector2f{10.0f, 10.0f};
    }

    void draw(sf::RenderWindow& win) const {
        win.draw(graphic_);
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
            g_.process(g_.vertexFromId(selected->vert.id));
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

    void loadFromGraph() {
        std::for_each(g_.vertexBegin(), g_.vertexEnd(),
                [this](graphs::Vertex& v) {
                    if (std::find_if(nodes_.begin(), nodes_.end(),
                            [&](Node const& n) {
                                return n.vert.id == v.id;
                            }) == nodes_.end()) {
                        nodes_.push_back(Node{v, createPos_});
                    }
                });
        edges_.clear();
        std::for_each(g_.edgeBegin(), g_.edgeEnd(),
                [this](graphs::Edge const& e) {
                    // Find the position in the node graph of the first vertex
                    // associated to the edge
                    auto node1 = std::find_if(nodes_.begin(), nodes_.end(),
                            [&](Node const& n) {
                                return n.vert.id == e.v1;
                            }) - nodes_.begin(); 
                    // Find the position in the node graph of the second vertex
                    // associated to the edge
                    auto node2 = std::find_if(nodes_.begin(), nodes_.end(),
                            [&](Node const& n) {
                                return n.vert.id == e.v2;
                            }) - nodes_.begin();
                    edges_.push_back(std::make_tuple(node1, node2, e.id));
                });
        selected_ = nodes_.end();
    }
};


}

#endif // NODE_HPP
