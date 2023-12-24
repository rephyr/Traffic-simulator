#ifndef VEHICLE_HH
#define VEHICLE_HH
#include <utility>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
struct spawn_point;
enum class Direction;

extern std::vector<spawn_point> spawn_points;
extern std::map<Direction, std::string> directions;

enum class Direction {
    Up,
    Down,
    Left,
    Right
};

struct coord {
    float x;
    float y;
};

struct spawn_point {
    coord location;
    Direction initial_direction;
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
    void set_acceleration(float acceleration);
    void set_speed(float i);
    void set_position(float x, float y);

    // Getters
    float get_speed() const;
    coord get_target_pos() const;
    coord get_position() const;
    Direction get_direction();
    const sf::CircleShape& get_shape() const;

    // Movement methods
    float calculate_speed();

    // Additional methods
    void update();
};
#endif // VEHICLE_HH
