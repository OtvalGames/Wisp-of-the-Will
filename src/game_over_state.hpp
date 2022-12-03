#ifndef GAME_OVER_STATE_HPP
#define GAME_OVER_STATE_HPP

#include "game.hpp"
#include "state.hpp"
#include "timer.hpp"

namespace yapg {
constexpr int gameover_buttons_count = 2;

class game_over_state : public state {
   private:
    enum buttons { again = 0, exit };

    game_data_ptr data;
    sf::Clock clock;
    timer& game_timer;

    sf::Sprite bg;
    sf::RectangleShape dim;
    std::deque<sf::Sprite*> buttons;

    bool is_exit;

   public:
    game_over_state(game_data_ptr _data, timer& _game_timer);

    void init();

    void handle_input();
    void update(float dt);
    void draw(float dt);
};
}  // namespace yapg

#endif // GAME_OVER_STATE_HPP
