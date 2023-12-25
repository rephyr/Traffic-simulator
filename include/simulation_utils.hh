#ifndef SIMULATION_UTILS_HH
#define SIMULATION_UTILS_HH

#include "vehicle.hh"
struct Intersection {
    sf::FloatRect area;
    sf::RectangleShape shape;
};
sf::RectangleShape get_slowing_zone(const sf::RectangleShape& intersection_shape);
sf::RectangleShape get_stop_zone(const sf::RectangleShape& intersection_shape);
bool should_avoid(const Vehicle& current_vehicle, const Vehicle& other_vehicle);
void handleIntersectionLogic(Vehicle& vehicle, const sf::FloatRect& intersectionArea);
bool is_vehicle_in_slowing_zone(const Vehicle& vehicle, const sf::RectangleShape& intersection_shape);
bool is_vehicle_in_stop_zone(const Vehicle& vehicle, const sf::RectangleShape& intersection_shape);
bool is_intersection_occupied(const std::vector<std::unique_ptr<Vehicle>>& vehicles, const sf::RectangleShape& intersection_shape, const Vehicle& current_vehicle);
#endif // SIMULATION_UTILS_HH
