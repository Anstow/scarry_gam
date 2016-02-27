#include <chrono>
#include <thread>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Tank/System/Controller.hpp>

void handle_tank_controllers(sf::Event const&);

int main()
{
    const std::chrono::duration<double> frame_duration(1.0/60.0);

    sf::RenderWindow window({320,320}, "Scarry Gam", sf::Style::Titlebar
                                                   | sf::Style::Resize);

    sf::Texture vert_00_tx;
    vert_00_tx.loadFromFile("res/gfx/vert_00.png");

    sf::Sprite test_vert {vert_00_tx};

    while (window.isOpen())
    {
        const auto frame_start = std::chrono::system_clock::now();
        const auto frame_end = frame_start + frame_duration;

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
                v.setCenter(0,0);
                window.setView(v);
                break;
                }
            default:
                break;
            }
        }

        window.clear();
        window.draw(test_vert);
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
