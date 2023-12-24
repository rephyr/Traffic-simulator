#include <SFML/Graphics.hpp>
#include "vehicle.hh"
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Vehicle Simulation");

    // Create roads
    sf::RectangleShape vertical_road(sf::Vector2f(60, 600)); // Width of 60, height of 600
    vertical_road.setPosition(370, 0);
    vertical_road.setFillColor(sf::Color(200, 200, 200)); // A gray color for the road

    sf::RectangleShape horizontal_road(sf::Vector2f(800, 60)); // Width of 800, height of 60
    horizontal_road.setPosition(0, 270);
    horizontal_road.setFillColor(sf::Color(200, 200, 200)); // Same gray color
    sf::Clock clock;

    // Keep track of all the vehicles
    std::vector<Vehicle> vehicles;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if (clock.getElapsedTime().asSeconds() >= 0.5f) {
            // Set colors for different spawns
            sf::Color bottom_spawn_color = sf::Color::Red;
            sf::Color top_spawn_color = sf::Color::Blue;
            sf::Color left_spawn_color = sf::Color::Green;
            sf::Color right_spawn_color = sf::Color::Yellow;

            // Select spawn point randomly
            int index = std::rand() % spawn_points.size();
            const spawn_point& selected_spawn_point = spawn_points[index];
            sf::Color spawn_color;

            switch (selected_spawn_point.initial_direction) {
                case Direction::Up:    // Bottom spawn
                    spawn_color = bottom_spawn_color;
                    break;
                case Direction::Down:  // Top spawn
                    spawn_color = top_spawn_color;
                    break;
                case Direction::Left:  // Right spawn
                    spawn_color = right_spawn_color;
                    break;
                case Direction::Right: // Left spawn
                    spawn_color = left_spawn_color;
                    break;
            }
            // Create new vehicle
            Vehicle new_vehicle(0.01f, 0.05f, 0.1f, 
                selected_spawn_point.location, selected_spawn_point.initial_direction, spawn_color);
            vehicles.push_back(new_vehicle);

            clock.restart();
        }

        // Update vehicle positions
        for (auto& vehicle : vehicles) {
            vehicle.update();
        }

        window.clear(sf::Color::White);

        // Draw roads
        window.draw(vertical_road);
        window.draw(horizontal_road);
        // Draw vehicles
        for (const auto& vehicle : vehicles) {
            window.draw(vehicle.get_shape());
        }

        window.display();
    }
    return 0;
}