#include <SFML/Graphics.hpp>
#include <chrono>

#include "Node.hpp"

#include <iostream>

constexpr std::chrono::milliseconds mouseDelay{200};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Viewer");

    using namespace drawing;


    std::cout << "Before creating graph." << std::endl;
    Graph g(window.getView().getCenter());
    std::cout << "After creating graph." << std::endl;

    std::chrono::steady_clock::time_point mouseDownTime;
    bool buttonPressed = false;
    bool selecting = false;

    while(window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Handle mouse input
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (not buttonPressed) {
                buttonPressed = true;
                mouseDownTime = std::chrono::steady_clock::now();
            }
            if (mouseDownTime - std::chrono::steady_clock::now() > mouseDelay) {
                if (not selecting) {
                    selecting = true;
                    g.clickHold(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                } else {
                    g.mouseMoved(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                }
            } 
        } else {
            if (buttonPressed and not selecting) {
                g.clickRelease(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
            }
            buttonPressed = false;
            selecting = false;
        }

        window.clear();
        g.draw(window);
        window.display();
    }

    return EXIT_SUCCESS;
}
