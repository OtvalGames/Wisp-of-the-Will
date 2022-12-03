#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "game.hpp"

namespace yapg {
enum direction { up, down, stay };

class player_ {
   public:
    player_(game_data_ptr _data);

    void init(game_data_ptr _data);

    void animate();
    void draw();

    void handle_input(sf::Event event);

    void update(float dt);
    void movement(float dt);

    void set_speed(unsigned int _speed);
    unsigned int get_speed();

    void set_position(sf::Vector2f point);
    sf::Vector2f get_position();

    unsigned int get_direction();

    sf::Sprite& get_sprite();

   private:
    game_data_ptr data;
    sf::Clock clock;

    sf::Sprite sprite;
    std::vector<sf::Texture>* animations;
    unsigned int animation_iterator;

    unsigned int direction;
    unsigned int vspeed;
};
}  // namespace yapg

#endif
