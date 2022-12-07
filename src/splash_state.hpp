#ifndef SPLASH_STATE_HPP
#define SPLASH_STATE_HPP

#include "game.hpp"
#include "state.hpp"

namespace wotw {
class splash_state : public state {
   private:
    game_data_ptr data;
    sf::Clock clock;
    sf::Sprite bg;
    sf::RectangleShape dim;

   public:
    splash_state(game_data_ptr _data);

    void init();

    void handle_input();
    void update(float dt);
    void draw(float dt);
    void close();
};
}  // namespace wotw

#endif  // SPLASH_STATE_HPP
