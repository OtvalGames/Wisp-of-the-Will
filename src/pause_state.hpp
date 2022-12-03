#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include "game.hpp"
#include "state.hpp"

namespace yapg {
constexpr float splash_fade_time = 0.7;
constexpr int pause_buttons_count = 2;

class pause_state : public state {
   private:
    enum buttons { go = 0, exit };

    game_data_ptr data;
    sf::Clock clock;

    sf::Sprite bg;
    sf::RectangleShape dim;
    std::deque<sf::Sprite*> buttons;

    bool is_exit;

   public:
    pause_state(game_data_ptr _data);

    void init();

    void handle_input();
    void update(float dt);
    void draw(float dt);
};
}  // namespace yapg

#endif  // PAUSE_STATE_HPP
