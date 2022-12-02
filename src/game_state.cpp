#include "game_state.hpp"

#include "pause_state.hpp"
#include "resources.hpp"

namespace yapg {
game_state::game_state(game_data_ptr _data) : data(_data) {}

void game_state::init() {
    srand(time(NULL));

    _walls = new walls(data);

    sf::View view;
    view.setCenter(0, 0);
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
            if (e.key.code == sf::Keyboard::Escape)
                data->machine.add_state(state_ptr(new pause_state(data)));
        }
    }
}

void game_state::update(float dt) { _walls->move(dt); }

void game_state::draw(float dt) {
    data->window.clear(sf::Color(0, 5, 25));

    _walls->draw();

    data->window.display();
}
}  // namespace yapg
