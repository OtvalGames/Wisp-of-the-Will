#ifndef WALLS_HPP
#define WALLS_HPP

#include "game.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

namespace yapg {
class walls {
   public:
    walls(game_data_ptr _data);

    void move(float dt);
    void draw();

   private:
    game_data_ptr data;

    std::vector<sf::Sprite> sprites;

    int move_speed;
};
}  // namespace yapg

#endif
