#include "obstacle.hpp"

namespace yapg {
obstacle::obstacle(game_data_ptr _data) : data(_data) { is_active = true; }

void obstacle::move(sf::Vector2f _offset) { sprite.move(_offset); }

void obstacle::draw() { data->window.draw(sprite); }

void obstacle::set_position(sf::Vector2f _position) { sprite.setPosition(_position); }

void obstacle::set_position(float x, float y) { sprite.setPosition(x, y); }

sf::Vector2f obstacle::get_position() { return sprite.getPosition(); }

void obstacle::activate() { is_active = true; }

void obstacle::disable() { is_active = false; }

bool obstacle::active() { return is_active; }

}  // namespace yapg
