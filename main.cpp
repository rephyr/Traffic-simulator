#include <SFML/Graphics.hpp>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Simple Intersection");

    // Set up the colors
    sf::Color gray(200, 200, 200);
    sf::Color white(255, 255, 255);

    // Create two rectangles to represent the roads
    sf::RectangleShape verticalRoad(sf::Vector2f(60, 600));
    verticalRoad.setPosition(370, 0);
    verticalRoad.setFillColor(gray);

    sf::RectangleShape horizontalRoad(sf::Vector2f(800, 60));
    horizontalRoad.setPosition(0, 270);
    horizontalRoad.setFillColor(gray);

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear screen
        window.clear(white);

        // Draw the roads
        window.draw(verticalRoad);
        window.draw(horizontalRoad);

        // Update the window
        window.display();
    }

    return 0;
}
