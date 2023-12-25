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

