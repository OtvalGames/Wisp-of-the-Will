#include "pause_state.hpp"

#include "main_menu_state.hpp"
#include "resources.hpp"

namespace yapg {
pause_state::pause_state(game_data_ptr _data, timer* _game_timer)
    : data(_data), game_timer_ptr(_game_timer) {
    game_timer_ptr->pause();
}

void pause_state::init() {
    // BG
    data->assets.load_texture("Pause Background", PAUSE_BG_FILEPATH);
    bg.setTexture(data->assets.get_texture("Pause Background"));

    bg.setPosition(data->window.mapPixelToCoords(sf::Vector2i(0, 0)));
    fit_sprite_size(bg, sf::Vector2f(data->window.getSize()));

    // Dim
    dim.setPosition(bg.getPosition());
    dim.setSize(sf::Vector2f(data->window.getSize()));

    // Buttons
    data->assets.load_texture("Go Button", GO_BUTTON_FILEPATH);
    data->assets.load_texture("Exit Button", EXIT_BUTTON_FILEPATH);

    for (int i = 0; i < pause_buttons_count; i++) {
        buttons.push_back(new sf::Sprite);
    }

    // Go button
    sf::Sprite* go_button = buttons.at(buttons::go);
    go_button->setTexture(data->assets.get_texture("Go Button"));
    go_button->setPosition(
        bg.getPosition().x + bg.getGlobalBounds().width / 2 - go_button->getGlobalBounds().width / 2,
        bg.getPosition().y + bg.getGlobalBounds().height / 2 - go_button->getGlobalBounds().height);

    // Exit button
    buttons.at(buttons::exit)->setTexture(data->assets.get_texture("Exit Button"));
    buttons.at(buttons::exit)
        ->setPosition(go_button->getPosition().x,
                      go_button->getPosition().y + go_button->getGlobalBounds().height * menu_buttons_gap_mul);

    is_exit = false;
}

void pause_state::handle_input() {
    sf::Event e;

    while (data->window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) data->window.close();

        if (e.type == sf::Event::KeyPressed)
            if (e.key.code == sf::Keyboard::Escape) {
                game_timer_ptr->start();
                data->machine.remove_state();
                break;
            }

        if (is_clicked(*buttons.at(buttons::go), sf::Mouse::Left, data->window)) {
            // Go button clicked
            game_timer_ptr->start();

            data->machine.remove_state();
        } else if (is_clicked(*buttons.at(buttons::exit), sf::Mouse::Left, data->window)) {
            // Exit button clicked

            is_exit = true;

            clock.restart();
        }
    }
}

void pause_state::update(float dt) {
    constexpr float splash_fade_time = 0.7;

    float time_elapsed = clock.getElapsedTime().asSeconds();

    if (time_elapsed < splash_fade_time) {
        int dim_lvl = static_cast<int>(time_elapsed * 255 / splash_fade_time) % 255;

        // BG Fade In
        dim.setFillColor(sf::Color(0, 0, 0, 255 - dim_lvl));
    } else
        dim.setFillColor(sf::Color(0, 0, 0, 0));

    if (is_exit) {
        if (time_elapsed < splash_fade_time) {
            int dim_lvl = static_cast<int>(time_elapsed * 255 / splash_fade_time) % 255;

            // BG Fade In
            dim.setFillColor(sf::Color(0, 0, 0, 0 + dim_lvl));
        } else {
            dim.setFillColor(sf::Color(0, 0, 0, 255));

            // Delete states
            data->machine.clear_states();
            // Start main menu state
            data->machine.add_state(state_ptr(new main_menu_state(data)));
        }
    }
}

void pause_state::draw(float dt) {
    data->window.clear();

    data->window.draw(bg);

    for (const sf::Sprite* b : buttons) data->window.draw(*b);

    data->window.draw(dim);

    data->window.display();
}
}  // namespace yapg
