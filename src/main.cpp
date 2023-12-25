#include <SFML/Graphics.hpp>
#include "vehicle.hh"
#include "simulation_utils.hh"
#include "road.hh"
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

bool is_outside_screen(const std::unique_ptr<Vehicle>& vehicle) {
    coord position = vehicle->get_position();
    return position.x < 0 || position.x > SCREEN_WIDTH || position.y < 0 || position.y > SCREEN_HEIGHT;
}

void remove_vehicle_outside_screen(std::vector<std::unique_ptr<Vehicle>>& vehicles) {
    vehicles.erase(
        std::remove_if(vehicles.begin(), vehicles.end(), 
                       [](const std::unique_ptr<Vehicle>& v) { return is_outside_screen(v); }),
        vehicles.end()
    );
}


int main() {

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Vehicle Simulation");

    // Create roads
    sf::RectangleShape vertical_road(sf::Vector2f(60, 600)); // Width of 60, height of 600
    vertical_road.setPosition(370, 0);
    vertical_road.setFillColor(sf::Color(200, 200, 200)); // A gray color for the road

    sf::RectangleShape horizontal_road(sf::Vector2f(800, 60)); // Width of 800, height of 60
    horizontal_road.setPosition(0, 270);
    horizontal_road.setFillColor(sf::Color(200, 200, 200)); // Same gray color

    sf::FloatRect vertical_roadBounds = vertical_road.getGlobalBounds();
    sf::FloatRect horizonta_roadBounds = horizontal_road.getGlobalBounds();
    sf::FloatRect intersectionArea;
    if (vertical_road.getGlobalBounds().intersects(horizontal_road.getGlobalBounds(), intersectionArea)) {
        // Expand the intersection area
        float expansionAmount = 40.0f; // Amount to expand the intersection area by
        intersectionArea.left -= expansionAmount / 2.0f;
        intersectionArea.top -= expansionAmount / 2.0f;
        intersectionArea.width += expansionAmount;
        intersectionArea.height += expansionAmount;
    }
    sf::RectangleShape intersection_shape;
    intersection_shape.setSize(sf::Vector2f(intersectionArea.width, intersectionArea.height));
    intersection_shape.setPosition(intersectionArea.left, intersectionArea.top);
    intersection_shape.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red fill
    intersection_shape.setOutlineColor(sf::Color(0, 0, 0)); // Black outline
    intersection_shape.setOutlineThickness(2.0f);

    // init intersection
    Intersection intersection;
    intersection.area = intersection_shape.getGlobalBounds();
    intersection.shape = intersection_shape;

    // Init time
    sf::Clock clock;

    // Keep track of all the vehicles
    std::vector<std::unique_ptr<Vehicle>> vehicles;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if (clock.getElapsedTime().asSeconds() >= 1.0f) {
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
            float vehicle_initial_speed = 0.01f;
            float vehicle_inital_acceleration = 0.0001f;
            float vehicle_inital_top_speed = 0.03f;
            
            vehicles.push_back(std::make_unique<Vehicle>(vehicle_initial_speed, 
                vehicle_inital_acceleration, vehicle_inital_top_speed, 
                    selected_spawn_point.location, selected_spawn_point.initial_direction, spawn_color));

            clock.restart();
        }

        // FIXME: Implement more efficient collision logic

        // Collision logic
        // Reset collision status for all vehicles
        for (auto& vehicle : vehicles) {
            vehicle->set_in_collision(false);

            // Check for collisions and update collision status
            for (size_t j = 0; j < vehicles.size(); j++) {
                if (vehicle.get() != vehicles[j].get()) {
                    if (vehicle->get_red_zone().getGlobalBounds().intersects(vehicles[j]->get_shape().getGlobalBounds())) {
                        if (should_avoid(*vehicle, *vehicles[j])) {
                            vehicle->set_in_collision(true);
                            vehicle->stop_car();
                            break;
                        }
                    } else if (vehicle->get_yellow_zone().getGlobalBounds().intersects(vehicles[j]->get_shape().getGlobalBounds())) {
                        if (should_avoid(*vehicle, *vehicles[j])) {
                            vehicle->set_in_collision(true);
                            vehicle->slow_down();
                        }
                    }
                }
            }

            // Intersection handling
            if(!vehicle->get_collision_status()){
                bool is_in_slowing_zone = is_vehicle_in_slowing_zone(*vehicle, intersection_shape);
                bool is_in_stop_zone = is_vehicle_in_stop_zone(*vehicle, intersection_shape);
                bool is_in_intersection = intersection_shape.getGlobalBounds().intersects(vehicle->get_shape().getGlobalBounds());

                if (is_in_slowing_zone && !is_in_intersection && !is_in_stop_zone) {
                    vehicle->set_intersection_state(IntersectionState::ApproachingIntersection);
                    if (is_intersection_occupied(vehicles, intersection_shape, *vehicle)) {
                        vehicle->slow_down();
                        std::cout << "slowing";
                    }
                } 
                else if (is_in_stop_zone && !is_in_intersection && vehicle->get_intersection_state() == IntersectionState::ApproachingIntersection) {
                    if (is_intersection_occupied(vehicles, intersection_shape, *vehicle)) {
                        vehicle->set_intersection_state(IntersectionState::ApproachingIntersection);
                        vehicle->stop_car();
                        std::cout << "stop";
                    }
                }
                else if (is_in_intersection) {
                    vehicle->set_intersection_state(IntersectionState::InIntersection);
                    vehicle->resume();
                    std::cout << "in inter";
                } 
                else if (is_in_slowing_zone) {
                    vehicle->set_intersection_state(IntersectionState::ExitingIntersection);
                    vehicle->resume();
                    std::cout << "exiting";
                } 
                else {
                    vehicle->set_intersection_state(IntersectionState::NotInIntersection);
                }

                // Update vehicle state
                if (!vehicle->get_collision_status() && vehicle->get_intersection_state() != IntersectionState::InIntersection) {
                    vehicle->resume();
                }
            }

            vehicle->update();
        }

        remove_vehicle_outside_screen(vehicles);

        sf::RectangleShape slowing_zone = get_slowing_zone(intersection_shape);
        sf::RectangleShape stopping_zone = get_stop_zone(intersection_shape);

        window.clear(sf::Color::White);

        // Draw the zones
        window.draw(slowing_zone);
        window.draw(stopping_zone);

        // Draw roads and vehicles
        window.draw(vertical_road);
        window.draw(horizontal_road);
        // Draw vehicles
        for (const auto& vehicle : vehicles) {
            window.draw(vehicle->get_yellow_zone());
            window.draw(vehicle->get_red_zone());
            window.draw(vehicle->get_shape());
        }

        window.display();
    }
    
    return 0;
}