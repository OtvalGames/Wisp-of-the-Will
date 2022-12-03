#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>

#include "game.hpp"

namespace yapg {
class obstacle {
   public:
    obstacle(game_data_ptr _data);

    void move(sf::Vector2f _offset);

    void draw();

    void set_position(sf::Vector2f _position);
    void set_position(float x, float y);
    sf::Vector2f get_position();

    sf::FloatRect get_global_bounds();

    void set_texture(sf::Texture& _texture);
    void set_texture_rect(sf::IntRect _rect);

    void activate();
    void disable();
    bool active();

   private:
    game_data_ptr data;

    sf::Sprite sprite;

    bool is_active;
};
}  // namespace yapg

#endif
