#ifndef WALLS_HPP
#define WALLS_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "game.hpp"

namespace yapg {
class walls {
   public:
    walls(game_data_ptr _data);

    void move(float dt);
    void draw();

    void set_move_speed(float _speed);
    int get_move_speed();

   private:
    game_data_ptr data;

    std::vector<sf::Sprite> sprites;

    float move_speed;
};
}  // namespace yapg

#endif
