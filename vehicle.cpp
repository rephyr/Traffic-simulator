// Vehicle.cpp
#include "vehicle.hh"

Vehicle::Vehicle(float init_speed, float init_acc, const float init_top_speed, coord init_pos, Direction init_dir, sf::Color color)
    : speed(init_speed), acceleration(init_acc), top_speed(init_top_speed), position(init_pos), direction(init_dir)
{
    float radius = 5.0f;
    shape.setFillColor(color); // Example color
    shape.setRadius(radius);
    // Set the initial position of the shape
    shape.setPosition(position.x, position.y);
}
void Vehicle::update(){
    Direction cur_dir = get_direction();
    coord cur_pos = get_position();
    float cur_speed = get_speed();
    cur_speed = calculate_speed();

    if (cur_dir == Direction::Up) {
        set_position(cur_pos.x, cur_pos.y - cur_speed); // Moving up typically decreases the y-coordinate
    } else if (cur_dir == Direction::Down) {
        set_position(cur_pos.x, cur_pos.y + cur_speed); // Moving down typically increases the y-coordinate
    } else if (cur_dir == Direction::Left) {
        set_position(cur_pos.x - cur_speed, cur_pos.y); // Moving left typically decreases the x-coordinate
    } else if (cur_dir == Direction::Right) {
        set_position(cur_pos.x + cur_speed, cur_pos.y); // Moving right typically increases the x-coordinate
    }
}
    
void Vehicle::move_car() {
    // Example movement logic: moves the vehicle downwards
    position.y += speed;
    shape.setPosition(position.x, position.y);
}

float Vehicle::calculate_speed() {
    if(speed += acceleration >= top_speed){
        return speed;
    } else{
        speed += acceleration;
        return speed;
    }
}

void Vehicle::set_direction(Direction dir) {
    direction = dir;
    // Implement logic to change the vehicle's direction based on the string
}

coord Vehicle::get_target_pos() const{
    return target_position;
}

float Vehicle::get_speed() const{
    return speed;
}

coord Vehicle::get_position() const{
    return position;
}
Direction Vehicle::get_direction(){
    return direction;
}
void Vehicle::set_acceleration(float i){
    acceleration = i;
}
void Vehicle::set_position(float x, float y) {
    position.x = x;
    position.y = y;
    shape.setPosition(x, y);
}
const sf::CircleShape& Vehicle::get_shape() const {
    return shape;
}