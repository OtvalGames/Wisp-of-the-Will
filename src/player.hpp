#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "game.hpp"

namespace wotw {
class player_ {
   public:
    player_(game_data_ptr _data);

    void init();
    void draw();
    void handle_input(sf::Event event);
    void update(float dt);

    void animate();

    void set_position(sf::Vector2f point);
    sf::Vector2f get_position();

    sf::Sprite& get_sprite();

   private:
    game_data_ptr data;
    sf::Clock clock;

    sf::Sprite sprite;
    std::deque<sf::Texture> animations;
    unsigned int animation_iterator;
};
}  // namespace wotw

#endif
