#include <SFML/Graphics.hpp>
#include <chrono>

#include "Node.hpp"

constexpr std::chrono::milliseconds mouseDelay{100};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Viewer");

    using namespace drawing;


    Graph g(window.getView().getCenter());

    std::chrono::steady_clock::time_point mouseDownTime;
    bool leftButtonPressed = false;
    bool selecting = false;

    bool rightButtonPressed = false;
    bool simulating = true;

    while(window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Handle mouse input
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (not leftButtonPressed) {
                leftButtonPressed = true;
                mouseDownTime = std::chrono::steady_clock::now();
            }
            if (std::chrono::steady_clock::now() - mouseDownTime > mouseDelay) {
                if (not selecting) {
                    selecting = true;
                    g.clickHold(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                } else {
                    g.mouseMoved(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                }
            } 
        } else {
            if (leftButtonPressed and not selecting) {
                g.clickRelease(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
            }
            leftButtonPressed = false;
            selecting = false;

            if (simulating) 
                g.stepPhysics();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            rightButtonPressed = true;
        } else {
            if (rightButtonPressed) {
                simulating = not simulating;
            }
            rightButtonPressed = false;
        }

        // ESC closed the viewer
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        window.clear();
        g.draw(window);
        window.display();
    }

    return EXIT_SUCCESS;
}
