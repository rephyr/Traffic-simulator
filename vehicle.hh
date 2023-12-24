#ifndef VEHICLE_HH
#define VEHICLE_HH
#include <utility>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
enum class Direction {
    Up,
    Down,
    Left,
    Right
};

std::map<Direction, std::string> directionNames = {
    {Direction::Up, "up"},
    {Direction::Down, "down"},
    {Direction::Left, "left"},
    {Direction::Right, "right"}
};

struct coord {
    float x;
    float y;
};
struct spawn_point {
    coord location;
    Direction initial_direction;
};

std::vector<spawn_point> spawn_points = {
    {{395 + 15, 600.0f}, Direction::Up},    // Bottom, goes up
    {{395 - 15, 0.0f}, Direction::Down},   // Top, goes down
    {{0.0f, 295 + 15}, Direction::Right},  // Left, goes right
    {{800.0f, 295 - 15}, Direction::Left}   // Right, goes left
};

class Vehicle {
private:
    float speed;
    float acceleration;  
    const float top_speed;
    coord position;
    Direction direction;
    coord target_position;

    sf::CircleShape shape;
public:
    // Constructor
    Vehicle(float init_speed, float init_acc, float init_top_speed, coord init_pos, Direction init_dir, sf::Color color);

    // Setters
    void set_acceleration(float acceleration); // Changed parameter type to float
    void set_direction(Direction direction); // Changed parameter type for clarity
    void set_speed(float i);
    void set_position(float x, float y);
    // Movement methods
    void move_car();
    float calculate_speed();

    // Getters
    float get_speed() const;
    coord get_target_pos() const;
    coord get_position() const;
    Direction get_direction();
    const sf::CircleShape& get_shape() const;

    // Additional methods
    void update();
};
#endif // VEHICLE_HH
