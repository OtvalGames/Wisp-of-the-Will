#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "asset_manager.hpp"
#include "state_machine.hpp"

namespace yapg {
struct game_data {
    sf::RenderWindow window;
    state_machine machine;
    asset_manager assets;
    //    input_manager input;
};

typedef std::shared_ptr<game_data> game_data_ptr;

class game {
   public:
    game();

   private:
    void run();

    const float dt = 1.0f / 60;
    sf::Clock clock;

    game_data_ptr data = std::make_shared<game_data>();
};
}  // namespace yapg

#endif
