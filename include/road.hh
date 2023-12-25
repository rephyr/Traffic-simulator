#ifndef ROAD_HH
#define ROAD_HH

class Road {
public:
    // Constructor
    Road(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color);

    // Accessors
    sf::RectangleShape get_shape() const;
    std::vector<spawn_point> get_spawn_points() const;

private:
    sf::RectangleShape shape;
    std::vector<spawn_point> spawn_points;

    void calc_spawn();
};
#endif
