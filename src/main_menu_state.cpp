#include "main_menu_state.hpp"

#include "game_state.hpp"
#include "resources.hpp"

namespace yapg {
main_menu_state::main_menu_state(game_data_ptr _data) : data(_data) {}

void main_menu_state::init() {
    // BG
    data->assets.load_texture("Menu Background", MENU_BG_FILEPATH);
    bg.setTexture(data->assets.get_texture("Menu Background"));

    bg.setPosition(0, 0);
    fit_sprite_size(bg, sf::Vector2f(data->window.getSize()));

    // Buttons
    data->assets.load_texture("Play Button", PLAY_BUTTON_FILEPATH);
    data->assets.load_texture("Exit Button", EXIT_BUTTON_FILEPATH);

    for (int i = 0; i < 2; i++) {
        buttons.push_back(new sf::Sprite);
    }

    // Go button
    sf::Sprite* play_button = buttons.at(buttons::play);
    play_button->setTexture(data->assets.get_texture("Play Button"));
    play_button->setPosition(
        bg.getPosition().x + bg.getGlobalBounds().width / 2 - play_button->getGlobalBounds().width / 2,
        bg.getPosition().y + bg.getGlobalBounds().height / 2 - play_button->getGlobalBounds().height);

    // Exit button
    buttons.at(buttons::exit)->setTexture(data->assets.get_texture("Exit Button"));
    buttons.at(buttons::exit)
        ->setPosition(play_button->getPosition().x,
                      play_button->getPosition().y + play_button->getGlobalBounds().height * 1.5);
}

void main_menu_state::handle_input() {
    sf::Event e;

    while (data->window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) data->window.close();

        if (is_clicked(*buttons.at(buttons::play), sf::Mouse::Left, data->window)) {
            // Go button clicked
            data->machine.add_state(state_ptr(new game_state(data)));
        } else if (is_clicked(*buttons.at(buttons::exit), sf::Mouse::Left, data->window)) {
            // Exit button clicked
            data->window.close();
        }
    }
}

void main_menu_state::update(float dt) {
    //    float time_elapsed = clock.getElapsedTime().asSeconds();
}

void main_menu_state::draw(float dt) {
    data->window.clear();

    data->window.draw(bg);
    for (const sf::Sprite* b : buttons) data->window.draw(*b);

    data->window.display();
}
}  // namespace yapg
