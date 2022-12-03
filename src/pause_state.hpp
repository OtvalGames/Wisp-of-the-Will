#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include "game.hpp"
#include "state.hpp"
#include "timer.hpp"

namespace yapg {
constexpr int pause_buttons_count = 2;

class pause_state : public state {
   private:
    enum buttons { go = 0, exit };

    game_data_ptr data;
    sf::Clock clock;
    timer* game_timer_ptr;

    sf::Sprite bg;
    sf::RectangleShape dim;
    std::deque<sf::Sprite*> buttons;

    bool is_exit;

   public:
    pause_state(game_data_ptr _data, timer* _game_timer);

    void init();

    void handle_input();
    void update(float dt);
    void draw(float dt);
};
}  // namespace yapg

#endif  // PAUSE_STATE_HPP
