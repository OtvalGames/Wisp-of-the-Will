#include "splash_state.hpp"

//#include "main_menu_state.hpp"
#include "game_state.hpp"
#include "resources.hpp"

namespace yapg {
splash_state::splash_state(game_data_ptr _data) : data(_data) {}

void splash_state::init() {
    data->assets.load_texture("Splash Background", SPLASH_BG_FILEPATH);

    bg.setTexture(data->assets.get_texture("Splash Background"));

    fit_sprite_size(bg, sf::Vector2f(data->window.getSize()));

    dim.setSize(sf::Vector2f(data->window.getSize()));
}

void splash_state::handle_input() {
    sf::Event e;

    typedef sf::Keyboard kb;

    while (data->window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) data->window.close();
        if (kb::isKeyPressed(kb::Enter) || kb::isKeyPressed(kb::Escape) || kb::isKeyPressed(kb::Space))
            data->machine.replace_state(state_ptr(new game_state(data)));
        // data->window.close();
    }
}

void splash_state::update(float dt) {
    float time_elapsed = clock.getElapsedTime().asSeconds();

    if (time_elapsed > splash_show_time)
               data->machine.replace_state(state_ptr(new game_state(data)));
        // data->window.close();

    if (time_elapsed < splash_fade_time) {
        int dim_lvl = static_cast<int>(time_elapsed * 255 / splash_fade_time) % 255;

        // BG Fade In
        dim.setFillColor(sf::Color(0, 0, 0, 255 - dim_lvl));
    } else
        dim.setFillColor(sf::Color(0, 0, 0, 0));
}

void splash_state::draw(float dt) {
    data->window.clear();

    data->window.draw(bg);
    data->window.draw(dim);

    data->window.display();
}
}  // namespace yapg
