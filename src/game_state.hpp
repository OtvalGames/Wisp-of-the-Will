#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "game.hpp"
#include "level.hpp"
#include "state.hpp"

namespace yapg {
class game_state : public state {
   private:
    game_data_ptr data;
    sf::Clock clock;

    level map;

   public:
    game_state(game_data_ptr _data);

    void init();

    void handle_input();
    void update(float dt);
    void draw(float dt);
};
}  // namespace yapg

#endif  // GAME_STATE_HPP
