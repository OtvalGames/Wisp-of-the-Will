#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>

#include "game.hpp"

namespace wotw {
constexpr int bonus_count = 3;
enum bonus { coin = 0, shield, skip };

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

    void set_bonus(bool b);
    bool bonus();

    void set_bonus_type(enum bonus bt);
    enum bonus get_bonus_type();

   private:
    game_data_ptr data;

    sf::Sprite sprite;

    bool is_active;

    bool is_bonus;
    enum bonus bonus_type;
};
}  // namespace wotw

#endif
