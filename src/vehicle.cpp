// Vehicle.cpp
#include "vehicle.hh"

std::map<Direction, std::string> directions = {
    {Direction::Up, "up"},
    {Direction::Down, "down"},
    {Direction::Left, "left"},
    {Direction::Right, "right"}
};

std::vector<spawn_point> spawn_points = {
    {{395 + 15, 600.0f}, Direction::Up},    
    {{395 - 15, 0.0f}, Direction::Down},  
    {{0.0f, 295 + 15}, Direction::Right}, 
    {{800.0f, 295 - 15}, Direction::Left}
};

Vehicle::Vehicle(float init_speed, float init_acc, float init_top_speed, coord init_pos, Direction init_dir, sf::Color color)
    : speed(init_speed), acceleration(init_acc), top_speed(init_top_speed), 
      position(init_pos), direction(init_dir), in_collision(false) {

    const int radius = 5;
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(position.x, position.y);

    // TODO: adjust these
    // Initialize yellow zone
    float yellow_zone_radius = 31.0f; // Example value
    yellow_zone.setRadius(yellow_zone_radius);
    yellow_zone.setFillColor(sf::Color(255, 255, 0, 100)); // Semi-transparent yellow
    yellow_zone.setOrigin(yellow_zone_radius, yellow_zone_radius); // Set origin to the center
    yellow_zone.setPosition(position.x, position.y);
    // Initialize red zone
    float red_zone_radius = 16.0f; // Example value
    red_zone.setRadius(red_zone_radius);
    red_zone.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red
    red_zone.setOrigin(red_zone_radius, red_zone_radius); // Set origin to the center
    red_zone.setPosition(position.x, position.y);
}


void Vehicle::update(){
    Direction cur_dir = get_direction();
    coord cur_pos = get_position();
    float cur_speed = get_speed();

    if(!in_collision){    
        cur_speed = calculate_speed();
    }

    if (cur_dir == Direction::Up) {
        set_position(cur_pos.x, cur_pos.y - cur_speed); 
    } else if (cur_dir == Direction::Down) {
        set_position(cur_pos.x, cur_pos.y + cur_speed); 
    } else if (cur_dir == Direction::Left) {
        set_position(cur_pos.x - cur_speed, cur_pos.y); 
    } else if (cur_dir == Direction::Right) {
        set_position(cur_pos.x + cur_speed, cur_pos.y); 
    }
    yellow_zone.setPosition(position.x, position.y);
    red_zone.setPosition(position.x, position.y);
}

void Vehicle::avoid(){

}

float Vehicle::calculate_speed() {
    if(speed += acceleration >= top_speed){
        return speed;
    } else{
        speed += acceleration;
        return speed;
    }
}

coord Vehicle::get_target_pos() const{
    return target_position;
}

bool Vehicle::get_collision_status(){
    return in_collision;
}
const sf::CircleShape& Vehicle::get_shape() const {
    return shape;
}

float Vehicle::get_speed() const{
    return speed;
}

coord Vehicle::get_position() const{
    return position;
}

Direction Vehicle::get_direction() const{
    return direction;
}
sf::FloatRect Vehicle::get_expanded_bounding_box() const {
    sf::FloatRect original_bounds = shape.getGlobalBounds();
    float expansion_factor = 1.5;
    original_bounds.left -= original_bounds.width * (expansion_factor - 1) / 2;
    original_bounds.top -= original_bounds.height * (expansion_factor - 1) / 2;
    original_bounds.width *= expansion_factor;
    original_bounds.height *= expansion_factor;
    return original_bounds;
}

void Vehicle::set_acceleration(float i){
    acceleration = i;
}

void Vehicle::set_position(float x, float y) {
    position.x = x;
    position.y = y;
    shape.setPosition(x, y);
}

void Vehicle::set_speed(float new_speed){
    speed = new_speed;
}
void Vehicle::set_in_collision(bool state){
    in_collision = state;
}

const sf::CircleShape& Vehicle::get_yellow_zone() const {
    return yellow_zone;
}

const sf::CircleShape& Vehicle::get_red_zone() const {
    return red_zone;
}

void Vehicle::slow_down() {
    // Reduce speed, but don't stop completely
    speed = std::max(speed * 0.5f, min_speed);
}

void Vehicle::resume() {
    // Gradually increase speed back to normal or some logic to resume movement
    speed = std::min(speed + acceleration, top_speed);
}

void Vehicle::stop_car(){
    speed = 0.0f;
}