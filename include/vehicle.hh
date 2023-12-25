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

struct coord {
    float x;
    float y;
};
// Intersection handling
enum class IntersectionState {
    NotInIntersection,
    ApproachingIntersection,
    InIntersection,
    ExitingIntersection
};
enum class Direction {
    Up,
    Down,
    Left,
    Right
};

struct spawn_point {
    coord location;
    Direction initial_direction;
};

class Vehicle {
private:
    // Speed data
    float speed;
    float acceleration;  
    float top_speed;
    float min_speed = 0.005f;

    // Position data
    coord position;
    Direction direction;
    coord target_position;

    // For vehicle avoidance and intersection handling
    sf::CircleShape yellow_zone;
    sf::CircleShape red_zone;
    bool in_collision;
    
    // Vehicle shape
    sf::CircleShape shape;

    IntersectionState intersectionState;


public:
    // Constructor
    Vehicle(float init_speed, float init_acc, float init_top_speed, coord init_pos, Direction init_dir, sf::Color color);

    // Setters
    void set_acceleration(float acceleration);
    void set_speed(float new_speed);
    void set_position(float x, float y);
    void set_in_collision(bool state);
    void set_intersection_state(IntersectionState state);

    // Getters
    float get_speed() const;
    coord get_target_pos() const;
    coord get_position() const;
    Direction get_direction() const;
    const sf::CircleShape& get_shape() const;
    sf::FloatRect get_expanded_bounding_box() const;
    bool get_collision_status();
    const sf::CircleShape& get_yellow_zone() const;
    const sf::CircleShape& get_red_zone() const;
    IntersectionState get_intersection_state() const;

    // Movement methods
    float calculate_speed();
    void slow_down();
    void stop_car();
    // Additional methods
    void avoid();
    void resume();
    void update();
};

#endif // VEHICLE_HH
