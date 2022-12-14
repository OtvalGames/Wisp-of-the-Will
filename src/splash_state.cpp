#include "splash_state.hpp"

#include "main_menu_state.hpp"
#include "resources.hpp"

namespace wotw {
splash_state::splash_state(game_data_ptr _data) : data(_data) {
    data->assets.load_texture("Splash Background", SPLASH_BG_FILEPATH);

    bg.setTexture(data->assets.get_texture("Splash Background"));

    fit_sprite_size(bg, sf::Vector2f(data->window.getSize()));

    dim.setSize(sf::Vector2f(data->window.getSize()));

    clock.restart();
}

splash_state::splash_state() { throw std::runtime_error("No data struct is allocated!\n"); }

void splash_state::handle_input() {
    sf::Event e;

    typedef sf::Keyboard kb;

    while (data->window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            data->window.close();
        else if (e.type == sf::Event::KeyPressed && e.key.code == kb::Enter ||
                 e.key.code == kb::Escape || e.key.code == kb::Space) {
            // Skip splash screen

            data->machine.replace_state(state_ptr(new main_menu_state(data)));
        }
    }
}

void splash_state::update(float dt) {
    constexpr float splash_fade_time = 1.0;
    constexpr float splash_show_time = 3.5;

    float time_elapsed = clock.getElapsedTime().asSeconds();

    if (time_elapsed > splash_show_time)
        data->machine.replace_state(state_ptr(new main_menu_state(data)));

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

splash_state::~splash_state() {}
}  // namespace wotw
