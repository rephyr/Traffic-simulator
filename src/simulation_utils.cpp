#include "simulation_utils.hh"

bool should_avoid(const Vehicle& current_vehicle, const Vehicle& other_vehicle) {
    Direction current_dir = current_vehicle.get_direction();
    Direction other_dir = other_vehicle.get_direction();

    if ((current_dir == Direction::Up && other_dir == Direction::Left) ||
        (current_dir == Direction::Left && other_dir == Direction::Down) ||
        (current_dir == Direction::Down && other_dir == Direction::Right) ||
        (current_dir == Direction::Right && other_dir == Direction::Up)) {
        return true;
    }
    // TODO: Implement more avoidance logic
    return false;

}
bool is_vehicle_in_slowing_zone(const Vehicle& vehicle, const sf::RectangleShape& intersection_shape) {
    float slowing_distance = 100.0f; // Adjust as needed
    sf::FloatRect slowing_area = intersection_shape.getGlobalBounds();
    slowing_area.left -= slowing_distance;
    slowing_area.top -= slowing_distance;
    slowing_area.width += slowing_distance * 2;
    slowing_area.height += slowing_distance * 2;

    return slowing_area.intersects(vehicle.get_shape().getGlobalBounds());
}

bool is_vehicle_in_stop_zone(const Vehicle& vehicle, const sf::RectangleShape& intersection_shape) {
    float stopping_distance = 50.0f; // Adjust as needed
    sf::FloatRect stopping_area = intersection_shape.getGlobalBounds();
    stopping_area.left -= stopping_distance;
    stopping_area.top -= stopping_distance;
    stopping_area.width += stopping_distance * 2;
    stopping_area.height += stopping_distance * 2;

    return stopping_area.intersects(vehicle.get_shape().getGlobalBounds());
}

bool is_intersection_occupied(const std::vector<std::unique_ptr<Vehicle>>& vehicles, const sf::RectangleShape& intersection_shape, const Vehicle& current_vehicle) {
    for (const auto& vehicle : vehicles) {
        if ((vehicle.get() != &current_vehicle) && intersection_shape.getGlobalBounds().intersects(vehicle->get_shape().getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

sf::RectangleShape get_slowing_zone(const sf::RectangleShape& intersection_shape) {
    float slowing_distance = 100.0f; 
    sf::FloatRect slowing_area = intersection_shape.getGlobalBounds();
    slowing_area.left -= slowing_distance;
    slowing_area.top -= slowing_distance;
    slowing_area.width += slowing_distance * 2;
    slowing_area.height += slowing_distance * 2;

    sf::RectangleShape slowing_zone;
    slowing_zone.setPosition(slowing_area.left, slowing_area.top);
    slowing_zone.setSize(sf::Vector2f(slowing_area.width, slowing_area.height));
    slowing_zone.setFillColor(sf::Color(255, 255, 0, 100)); // Semi-transparent yellow

    return slowing_zone;
}

sf::RectangleShape get_stop_zone(const sf::RectangleShape& intersection_shape) {
    float stopping_distance = 30.0f; 
    sf::FloatRect stopping_area = intersection_shape.getGlobalBounds();
    stopping_area.left -= stopping_distance;
    stopping_area.top -= stopping_distance;
    stopping_area.width += stopping_distance * 2;
    stopping_area.height += stopping_distance * 2;

    sf::RectangleShape stopping_zone;
    stopping_zone.setPosition(stopping_area.left, stopping_area.top);
    stopping_zone.setSize(sf::Vector2f(stopping_area.width, stopping_area.height));
    stopping_zone.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red

    return stopping_zone;
}