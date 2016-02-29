#include "Node.hpp"

using namespace drawing;

constexpr float vectorLength(sf::Vector2f const& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

float getRandom() {
    static std::minstd_rand gen_{100};

    return std::generate_canonical<float, 10>(gen_) * 2 - 1;
}

Node::Node(unsigned i, sf::Vector2f const& pos)
    : id(i) {
        graphic_.setPosition(pos);
        graphic_.setRadius(10.0f);
        graphic_.setFillColor({0,0,0,0});
        graphic_.setOutlineThickness(2.0f);
        graphic_.setOutlineColor({255,255,255});
    }

void Node::setPos(sf::Vector2f p) {
    graphic_.setPosition(p - sf::Vector2f{10.0f, 10.0f});
}

void Node::setColor(sf::Color const& c) {
    graphic_.setOutlineColor(c);
}

sf::Vector2f Node::getPos() const {
    return graphic_.getPosition() + sf::Vector2f{10.0f, 10.0f};
}

void Node::draw(sf::RenderWindow& win) const {
    win.draw(graphic_);
}

void Node::stepSim(float time) {
    vel_ *= damping;
    vel_ += time * force / nodeMass;
    force = {0,0};

    setPos(getPos() + vel_ * time);
}

// Graph


Graph::Graph(sf::Vector2f const& createPos)
    : createPos_(createPos)
{
    loadFromGraph();
}

void Graph::clickHold(sf::Vector2f const& pos) {
    selected_ = selectAt(pos);
    if (selected_ != nodes_.end()) {
        offset_ = selected_->getPos() - pos;
    }
}

void Graph::clickRelease(sf::Vector2f const& pos) {
    auto selected = selectAt(pos);
    if (selected != nodes_.end()) {
        g_.process(selected->id);
        loadFromGraph();
    }
}

void Graph::mouseMoved(sf::Vector2f const& pos) {
    if (selected_ != nodes_.end()) {
        selected_->setPos(pos + offset_);
    }
}

void Graph::draw(sf::RenderWindow& win) {
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

Graph::NodeItr Graph::selectAt(sf::Vector2f const& p) {
    return std::find_if(nodes_.begin(), nodes_.end(),
            [&](Node const& n) {
            auto d = (n.getPos() - p);
            return (d.x * d.x + d.y * d.y) < 100.0f;
            });
}

Graph::NodeItr Graph::getNodeFromId(unsigned id) {
    return std::find_if(nodes_.begin(), nodes_.end(),
            [=](Node const& n) {
            return n.id == id;
            }); 
}

void Graph::loadFromGraph() {
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
    return springConst * len;
}

float calcGenForce(float len) {
    (void) len;
    return - nodeSep / len;
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
    return calcSpringForceMag(l, defaultSpringConst) * offset / l;
}

/*!
 * \brief Calculates the force keeping nodes apart
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
    return calcGenForce(l) * offset / l;
}

void Graph::stepPhysics(float time) {
    // Calculates the gravity forces on each node
    for (auto n1 = nodes_.begin(); n1 != nodes_.end(); ++n1) {
        for (auto n2 = n1+1; n2 != nodes_.end(); ++n2) {
            auto f =  calcSingleNodeForce(*n1, *n2);
            n1->force += f;
            n2->force -= f;
        }
    }
    // Calulates the spring forces on each node
    std::for_each(edges_.begin(), edges_.end(),
            [=](Edge const& e) {
                auto forceVec = calcEdgeForce(nodes_[std::get<0>(e)], nodes_[std::get<1>(e)]);

                nodes_[std::get<0>(e)].force += forceVec;
                nodes_[std::get<1>(e)].force -= forceVec;
            });
    // Step the simulation and zero the forces
    std::for_each(nodes_.begin(), nodes_.end(),
            [=](Node& n) {
                n.stepSim(time);
            });
}
