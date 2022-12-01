#ifndef SPLASH_STATE_HPP
#define SPLASH_STATE_HPP

#include "game.hpp"
#include "state.hpp"

namespace bruh {
constexpr float splash_fade_time = 1.0;
constexpr float splash_show_time = 3.5;

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
};
}  // namespace bruh

#endif  // SPLASH_STATE_HPP
