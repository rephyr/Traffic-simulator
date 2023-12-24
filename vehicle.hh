#ifndef VEHICLE_HH
#define VEHICLE_HH
#include <utility>
struct coord {
    float x;
    float y;
};

class Vehicle {
private:
    float speed;
    float const acceleration;
    
    coord position;
    coord const target_position;
public:
    Vehicle();

    void move_car();
    void calculate_speed()
    coord get_position();
};

#endif // VEHICLE_HH
