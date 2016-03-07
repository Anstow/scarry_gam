#include <chrono>
#include <iterator>
#include <memory>
#include <thread>
#include <unordered_map>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <Tank/System/Controller.hpp>
#include "../graphs/graph.hpp"

#include "Player.hpp"
#include "Node.hpp"

#include "../input/ControllerInput.hpp"
#include "../input/KeyboardInput.hpp"

using NodeID = unsigned;

constexpr unsigned frames_per_second = 60;
constexpr std::chrono::duration<double> frame_duration(1.0/frames_per_second);

std::unordered_map<NodeID, Node> nodes;
std::vector<sf::Sprite> screens;
// This is horible perhaps Player should be std::unique_ptr
// TODO(David): don't leek players!
std::vector<std::pair<Player*, std::unique_ptr<sf::RenderTexture>>> players;
sf::RenderWindow window;

void handle_events(sf::RenderWindow&);
void handle_tank_controllers(sf::Event const&);
void create_split_screen();
void draw_world(graphs::MapGraph const&, NodeID, sf::RenderTarget& target);
void draw_node(NodeID, sf::RenderTarget& target, unsigned n_edges);
std::vector<NodeID> find_edges(graphs::MapGraph const&, NodeID);

int main()
{
    window.create({640,640}, "Scarry Gam", sf::Style::None
                                         | sf::Style::Titlebar
                                         //| sf::Style::Fullscreen
                                         | sf::Style::Close);


    graphs::MapGraph graph;

    tank::Controllers::initialize();

    // Add keyboard player
    {
        constexpr unsigned start_node = 0;

        Player* p = new Player(
                std::make_unique<input::KeyboardInput>(),
                &nodes[start_node]);
        players.emplace_back(
            std::make_pair//<Player*, std::unique_ptr<sf::RenderTexture>>
                (p,
                 std::unique_ptr<sf::RenderTexture>(new sf::RenderTexture)));
        nodes[start_node].addEntity(std::unique_ptr<Player>(p));
    }

    for (auto& c : tank::Controllers::getConnectedControllers())
    {
        constexpr unsigned start_node = 0;

        nodes[start_node].setID(start_node);
        Player* p = new Player(
                std::make_unique<input::ControllerInput>(*c),
                &nodes[start_node]);

        players.emplace_back(
            std::make_pair//<Player*, std::unique_ptr<sf::RenderTexture>>
                (p,
                 std::unique_ptr<sf::RenderTexture>(new sf::RenderTexture)));
        nodes[start_node].addEntity(std::unique_ptr<Player>(p));
    }

    create_split_screen();

    while (window.isOpen())
    {
        const auto frame_start = std::chrono::system_clock::now();
        const auto frame_end = frame_start + frame_duration;

        handle_events(window);

        // For testing purposes its a lot easy for me to press escape than to
        // close the window manually
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        for (auto& n : nodes) {
            std::get<1>(n).update();
        }


        window.clear();
        for (auto& p : players)
        {
            auto player = std::get<0>(p);
            auto& canvas = std::get<1>(p);

            auto node_id = player->getCurrentNode()->getID();

            auto v = canvas->getView();

            auto player_pos = player->getPos();
            v.setCenter(player_pos.x, player_pos.y);
            canvas->setView(v);
            canvas->clear();

            draw_world(graph, node_id, *canvas);

            canvas->display(); // make it not upside down ???????
        }

        for (auto const& screen : screens) {
            window.draw(screen);
        }
        window.display();

        std::this_thread::sleep_for(frame_end - std::chrono::system_clock::now());
    }
}

void handle_tank_controllers(sf::Event const& event)
{
    switch (event.type)
    {
    case sf::Event::JoystickConnected:
        tank::Controllers::setStatus(event.joystickConnect.joystickId, true);
        break;
    case sf::Event::JoystickDisconnected:
        tank::Controllers::setStatus(event.joystickConnect.joystickId, false);
        break;
    case sf::Event::JoystickMoved:
        tank::Controllers::setAxis(event.joystickMove.joystickId,
                             event.joystickMove.axis,
                             event.joystickMove.position);
        break;
    case sf::Event::JoystickButtonPressed:
        tank::Controllers::setButton(event.joystickButton.joystickId,
                               event.joystickButton.button, true);
        break;
    case sf::Event::JoystickButtonReleased:
        tank::Controllers::setButton(event.joystickButton.joystickId,
                               event.joystickButton.button, false);
        break;
    default:
        break;
    }
}

void create_split_screen()
{
    const sf::Vector2u size = window.getSize();

    const unsigned split_width = (players.size() > 1) ? (size.x / 2) : size.x;
    const unsigned split_height = (players.size() > 2) ? (size.y / 2) : size.y;

    screens.clear();

    
    for (int i = 0; i < players.size(); ++i)
    {
        const unsigned x = (size.x / 2) * (i % 2);
        const unsigned y = (size.y / 2) * (i / 2);

        auto& canvas = players[i].second;
        canvas->create(split_width, split_height);
        screens.emplace_back(canvas->getTexture());
        screens.back().setPosition(x, y);
    }
}

void draw_world(graphs::MapGraph const& graph, NodeID node_id,
                sf::RenderTarget& canvas)
{
    auto vert = graph.vertexFromId(node_id);

    if (vert != graph.cVertexEnd())
    {
        auto edges = find_edges(graph, node_id);
        draw_node(node_id, canvas, edges.size());
        /*
        for (NodeID e : edges)
        {
            draw_node(e, canvas, 2);
        }
        */
    }
    else
    {
        auto e = graph.edgeFromId(node_id);
        draw_node(node_id, canvas, 2);
        /*
        for (NodeID v : {e->v1, e->v2})
        {
            draw_node(v, canvas, find_edges(graph, v).size());
        }
        */
    }
}

void draw_node(NodeID node_id, sf::RenderTarget& canvas, unsigned n_edges)
{
    //int n_edges = isEdge ? 2 : find_edges(node_id).size();

    auto& node = nodes[node_id];
    nodes[node_id].setID(node_id); // Hehehehehehehehehehehehe
    if (node.edgeCount() != n_edges)
    {
        node.updateEdgeCount(n_edges);
    }
    node.draw(canvas);
}


std::vector<NodeID> find_edges(graphs::MapGraph const& g, NodeID id)
{
    std::vector<NodeID> result;
    for (auto e = g.cEdgeBegin(); e != g.cEdgeEnd(); ++e) {
        if (e->v1 == id or e->v2 == id)
        {
            result.push_back(e->id);
        }
    }
    return result;
}

void handle_events(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        handle_tank_controllers(event);

        switch(event.type)
        {
        case sf::Event::Closed:
            window.close(); break;
        case sf::Event::Resized:
            {
            auto v = window.getView();
            v.setSize(event.size.width, event.size.height);
            v.setCenter(event.size.width / 2, event.size.height / 2);
            window.setView(v);
            create_split_screen(); //XXX: This causes muchos lag
            break;
            }
        default:
            break;
        }
    }
}
