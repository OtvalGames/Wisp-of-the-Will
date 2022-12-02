#include "game_state.hpp"

#include "resources.hpp"

namespace bruh {
game_state::game_state(game_data_ptr _data) : data(_data) {}

void game_state::init() {
    srand(time(NULL));

    map.load_level(GAME_LVL_FILEPATH);

    sf::View view;
    view.setCenter(sf::Vector2f((float)(map.get_level_size().x * map.get_tile_size().x) / 2.0f,
                                (float)(map.get_level_size().y * map.get_tile_size().y) / 2.0f));
    view.setSize(data->window.getSize().x, data->window.getSize().y);

    data->window.setView(view);
}

void game_state::handle_input() {
    sf::Event e;

    while (data->window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            data->window.close();
        }

        if (e.type == sf::Event::KeyPressed) {
            data->window.close();
        }
    }
}

void game_state::update(float dt) {}

void game_state::draw(float dt) {
    data->window.clear(sf::Color(0, 5, 25));

    map.draw(data->window);

    data->window.display();
}
}  // namespace bruh
