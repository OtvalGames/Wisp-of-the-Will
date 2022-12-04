#include "game_over_state.hpp"

#include "game_state.hpp"
#include "main_menu_state.hpp"
#include "resources.hpp"

namespace yapg {
game_over_state::game_over_state(game_data_ptr _data, unsigned int _game_score, timer _game_timer)
    : data(_data), game_score(_game_score), game_timer(_game_timer) {}

void game_over_state::init() {
    // BG
    data->assets.load_texture("Game Over Background", GAMEOVER_BG_FILEPATH);
    bg.setTexture(data->assets.get_texture("Game Over Background"));

    bg.setPosition(data->window.mapPixelToCoords(sf::Vector2i(0, 0)));
    fit_sprite_size(bg, sf::Vector2f(data->window.getSize()));

    // Dim
    dim.setPosition(bg.getPosition());
    dim.setSize(sf::Vector2f(data->window.getSize()));

    // Buttons
    data->assets.load_texture("Again Button", AGAIN_BUTTON_FILEPATH);
    data->assets.load_texture("Exit Button", EXIT_BUTTON_FILEPATH);

    for (int i = 0; i < gameover_buttons_count; i++) {
        buttons.push_back(new sf::Sprite);
    }

    // Again button
    sf::Sprite* again_button = buttons.at(buttons::again);
    again_button->setTexture(data->assets.get_texture("Again Button"));
    again_button->setPosition(
        bg.getPosition().x + bg.getGlobalBounds().width / 2 - again_button->getGlobalBounds().width / 2,
        bg.getPosition().y + bg.getGlobalBounds().height / 2 - again_button->getGlobalBounds().height);

    // Exit button
    buttons.at(buttons::exit)->setTexture(data->assets.get_texture("Exit Button"));
    buttons.at(buttons::exit)
        ->setPosition(again_button->getPosition().x,
                      again_button->getPosition().y +
                          again_button->getGlobalBounds().height * menu_buttons_gap_mul);

    // Score
    score_font.loadFromFile(FONT_IMPACT);

    stats_text.setFont(score_font);
    stats_text.setCharacterSize(35);

    stats_text.setString("Your score: " + std::to_string(game_score));
    stats_text.setString(stats_text.getString() + "\nTime played: " +
                         std::to_string(static_cast<int>(game_timer.get_elapsed_seconds())) + "s");

    stats_text.setPosition(
        bg.getPosition().x + bg.getGlobalBounds().width / 2 - stats_text.getGlobalBounds().width / 2,
        bg.getPosition().y + bg.getGlobalBounds().height / 3 - stats_text.getGlobalBounds().height);

    is_exit = false;

    data->window.setMouseCursorVisible(true);
}

void game_over_state::handle_input() {
    sf::Event e;

    while (data->window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) data->window.close();

        if (e.type == sf::Event::KeyPressed)
            if (e.key.code == sf::Keyboard::Escape) {
                data->machine.remove_state();
                break;
            }

        if (is_clicked(*buttons.at(buttons::again), sf::Mouse::Left, data->window)) {
            // Again button clicked

            // Delete states
            data->machine.clear_states();
            // Start game state
            data->machine.add_state(state_ptr(new game_state(data)));
        } else if (is_clicked(*buttons.at(buttons::exit), sf::Mouse::Left, data->window)) {
            // Exit button clicked

            is_exit = true;
            clock.restart();
        }
    }
}

void game_over_state::update(float dt) {
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

void game_over_state::draw(float dt) {
    data->window.clear();

    data->window.draw(bg);

    for (const sf::Sprite* b : buttons) data->window.draw(*b);
    data->window.draw(stats_text);

    data->window.draw(dim);

    data->window.display();
}

void game_over_state::close() {}
}  // namespace yapg
