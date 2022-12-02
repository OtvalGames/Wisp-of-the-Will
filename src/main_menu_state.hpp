#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "game.hpp"
#include "state.hpp"

namespace yapg {
constexpr int buttons_count = 3;

enum buttons { play = 0, stat, exit };

class main_menu_state : public state {
   private:
    game_data_ptr data;
    sf::Clock clock;

    sf::Sprite bg;
    std::deque<sf::Sprite*> buttons;

   public:
    main_menu_state(game_data_ptr _data);

    void init();

    void handle_input();
    void update(float dt);
    void draw(float dt);
};
}  // namespace yapg

#endif  // MAIN_MENU_STATE_HPP
