#include "road.hh"

Road::Road(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(color);

    if (size.x > size.y) { // Horizontal road
        spawn_points.push_back({{position.x, position.y + size.y / 2}, Direction::Right});
        spawn_points.push_back({{position.x + size.x, position.y + size.y / 2}, Direction::Left});
    } else { // Vertical road
        spawn_points.push_back({{position.x + size.x / 2, position.y}, Direction::Down});
        spawn_points.push_back({{position.x + size.x / 2, position.y + size.y}, Direction::Up});
    }
}