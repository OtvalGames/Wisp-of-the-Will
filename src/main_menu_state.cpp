#include "main_menu_state.hpp"

#include "game_state.hpp"
#include "resources.hpp"

namespace yapg {
main_menu_state::main_menu_state(game_data_ptr _data) : data(_data) {}

void main_menu_state::init() {
    data->window.setView(data->window.getDefaultView());

    // BG
    data->assets.load_texture("Menu Background", MENU_BG_FILEPATH);
    bg.setTexture(data->assets.get_texture("Menu Background"));

    bg.setPosition(0, 0);
    fit_sprite_size(bg, sf::Vector2f(data->window.getSize()));

    // Buttons
    data->assets.load_texture("Play Button", PLAY_BUTTON_FILEPATH);
    data->assets.load_texture("Stat Button", STAT_BUTTON_FILEPATH);
    data->assets.load_texture("Exit Button", EXIT_BUTTON_FILEPATH);

    for (int i = 0; i < menu_buttons_count; i++) {
        buttons.push_back(new sf::Sprite);
    }

    // Go button
    sf::Sprite* play_button = buttons.at(buttons::play);
    play_button->setTexture(data->assets.get_texture("Play Button"));
    play_button->setPosition(
        bg.getPosition().x + bg.getGlobalBounds().width / 2 - play_button->getGlobalBounds().width / 2,
        bg.getPosition().y + bg.getGlobalBounds().height / 2 - play_button->getGlobalBounds().height);

    // Stat button
    sf::Sprite* stat_button = buttons.at(buttons::stat);
    stat_button->setTexture(data->assets.get_texture("Stat Button"));
    stat_button->setPosition(
        play_button->getPosition().x,
        play_button->getPosition().y + play_button->getGlobalBounds().height * menu_buttons_gap_mul);

    // Exit button
    buttons.at(buttons::exit)->setTexture(data->assets.get_texture("Exit Button"));
    buttons.at(buttons::exit)
        ->setPosition(
            stat_button->getPosition().x,
            stat_button->getPosition().y + stat_button->getGlobalBounds().height * menu_buttons_gap_mul);

    score_font.loadFromFile(FONT_IMPACT);

    best_score.setFont(score_font);
    best_score.setCharacterSize(35);

    unsigned int score = get_score_from_save();

    best_score.setString("Best score: " + std::to_string(score));

    best_score.setPosition(
        bg.getPosition().x + bg.getGlobalBounds().width / 2 - best_score.getGlobalBounds().width / 2,
        bg.getPosition().y + bg.getGlobalBounds().height / 3 - best_score.getGlobalBounds().height);
}

void main_menu_state::handle_input() {
    sf::Event e;

    while (data->window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) data->window.close();

        if (is_clicked(*buttons.at(buttons::play), sf::Mouse::Left, data->window)) {
            // Go button clicked
            data->machine.replace_state(state_ptr(new game_state(data)));
        } else if (is_clicked(*buttons.at(buttons::stat), sf::Mouse::Left, data->window)) {
            // Stat button clicked
            // TODO: Remove stats button
        } else if (is_clicked(*buttons.at(buttons::exit), sf::Mouse::Left, data->window)) {
            // Exit button clicked
            data->window.close();
        }
    }
}

void main_menu_state::update(float dt) {}

void main_menu_state::draw(float dt) {
    data->window.clear();

    data->window.draw(bg);

    for (const sf::Sprite* b : buttons) data->window.draw(*b);

    data->window.draw(best_score);

    data->window.display();
}
}  // namespace yapg
