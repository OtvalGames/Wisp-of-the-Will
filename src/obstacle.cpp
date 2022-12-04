#include "obstacle.hpp"

namespace yapg {
obstacle::obstacle(game_data_ptr _data) : data(_data), is_bonus(false) { is_active = false; }

void obstacle::move(sf::Vector2f _offset) { sprite.move(_offset); }

void obstacle::draw() { data->window.draw(sprite); }

void obstacle::set_position(sf::Vector2f _position) { sprite.setPosition(_position); }

void obstacle::set_position(float x, float y) { sprite.setPosition(x, y); }

sf::Vector2f obstacle::get_position() { return sprite.getPosition(); }

sf::FloatRect obstacle::get_global_bounds() { return sprite.getGlobalBounds(); }

void obstacle::set_texture(sf::Texture& _texture) { sprite.setTexture(_texture); }

void obstacle::set_texture_rect(sf::IntRect _rect) { sprite.setTextureRect(_rect); }

void obstacle::activate() { is_active = true; }

void obstacle::disable() { is_active = false; }

void obstacle::set_bonus(bool b) { is_bonus = b; }

bool obstacle::bonus() { return is_bonus; }

bool obstacle::active() { return is_active; }

}  // namespace yapg
