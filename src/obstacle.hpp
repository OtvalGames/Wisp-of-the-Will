#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "game.hpp"

#include <SFML/Graphics.hpp>

namespace yapg {
class obstacle {
   public:
    obstacle(game_data_ptr _data);

    void move(sf::Vector2f _offset);

    void draw();

    void set_position(sf::Vector2f _position);
    void set_position(float x, float y);
    sf::Vector2f get_position();

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
