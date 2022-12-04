#include "main_menu_state.hpp"

#include <fstream>

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

    // Exit button
    buttons.at(buttons::exit)->setTexture(data->assets.get_texture("Exit Button"));
    buttons.at(buttons::exit)
        ->setPosition(
            play_button->getPosition().x,
            play_button->getPosition().y + play_button->getGlobalBounds().height * menu_buttons_gap_mul);

    score_font.loadFromFile(FONT_IMPACT);

    best_score.setFont(score_font);
    best_score.setCharacterSize(35);

    unsigned int score = get_score_from_save();

    best_score.setString("Best score: " + std::to_string(score));

    best_score.setPosition(
        bg.getPosition().x + bg.getGlobalBounds().width / 2 - best_score.getGlobalBounds().width / 2,
        bg.getPosition().y + bg.getGlobalBounds().height / 3 - best_score.getGlobalBounds().height);

    data->assets.load_texture("Player Skin Preview Classic", PLAYER_SKIN_PREVIEW_CLASSIC_FILEPATH);
    data->assets.load_texture("Player Skin Preview Outline", PLAYER_SKIN_PREVIEW_OUTLINE_FILEPATH);
    data->assets.load_texture("Player Skin Preview Sharpen", PLAYER_SKIN_PREVIEW_SHARPEN_FILEPATH);
    data->assets.load_texture("Player Skin Preview Fire", PLAYER_SKIN_PREVIEW_FIRE_FILEPATH);

    std::ifstream skin_save_file(CURRENT_SKIN_FILEPATH);

    if (skin_save_file.is_open()) {
        std::string tmp;

        skin_save_file >> tmp;
        skin_save_file >> tmp;

        current_skin_id = (skins)std::stoi(tmp);
    } else {
        current_skin_id = skins::classic;
    }

    for (int i = 0; i < skins_count; i++) {
        sf::Sprite tmp;

        skins_sprites.push_back(tmp);
    }

    skins_sprites.at(skins::classic).setTexture(data->assets.get_texture("Player Skin Preview Classic"));
    skins_sprites.at(skins::classic).setScale(3, 3);
    skins_sprites.at(skins::classic)
        .setPosition(
            data->window.getView().getCenter().x -
                skins_sprites.at(skins::classic).getGlobalBounds().width / 2,
            best_score.getPosition().y - skins_sprites.at(skins::classic).getGlobalBounds().height * 2);

    skins_sprites.at(skins::outline).setTexture(data->assets.get_texture("Player Skin Preview Outline"));
    skins_sprites.at(skins::outline).setScale(3, 3);
    skins_sprites.at(skins::outline).setPosition(skins_sprites.at(skins::classic).getPosition());

    skins_sprites.at(skins::shapren).setTexture(data->assets.get_texture("Player Skin Preview Sharpen"));
    skins_sprites.at(skins::shapren).setScale(3, 3);
    skins_sprites.at(skins::shapren).setPosition(skins_sprites.at(skins::classic).getPosition());

    skins_sprites.at(skins::fire).setTexture(data->assets.get_texture("Player Skin Preview Fire"));
    skins_sprites.at(skins::fire).setScale(3, 3);
    skins_sprites.at(skins::fire).setPosition(skins_sprites.at(skins::classic).getPosition());

    current_skin_preview = &skins_sprites.at(current_skin_id);

    skins_filepaths[skins::classic] = PLAYER_ANIM_CLASSIC_FILEPATH;
    skins_filepaths[skins::outline] = PLAYER_ANIM_OUTLINE_FILEPATH;
    skins_filepaths[skins::shapren] = PLAYER_ANIM_SHARPEN_FILEPATH;
    skins_filepaths[skins::fire] = PLAYER_ANIM_FIRE_FILEPATH;

    data->assets.load_texture("Arrow Left", ARROW_LEFT_FILEPATH);
    data->assets.load_texture("Arrow Right", ARROW_RIGHT_FILEPATH);

    for (int i = 0; i < 2; i++) {
        sf::Sprite tmp;

        arrows.push_back(tmp);
    }

    arrows.at(arrows::left).setTexture(data->assets.get_texture("Arrow Left"));
    arrows.at(arrows::left)
        .setPosition(
            current_skin_preview->getPosition().x - arrows.at(arrows::left).getGlobalBounds().width - 10,
            current_skin_preview->getPosition().y + 15);

    arrows.at(arrows::right).setTexture(data->assets.get_texture("Arrow Right"));
    arrows.at(arrows::right)
        .setPosition(current_skin_preview->getGlobalBounds().left +
                         current_skin_preview->getGlobalBounds().width + 10,
                     current_skin_preview->getPosition().y + 15);

    // Soundtrack
    constexpr float default_volume = 25;

    music.setLoop(true);
    music.setVolume(default_volume);

    if (music.openFromFile(OST_HM_DUST_FILEPATH)) music.play();
}

void main_menu_state::handle_input() {
    sf::Event e;

    while (data->window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) data->window.close();

        if (e.type == sf::Event::MouseWheelScrolled) {
            // Change music volume by scrolling mouse wheel

            float new_volume = music.getVolume() + e.mouseWheelScroll.delta;

            if (new_volume - 100 > 0.01)
                new_volume = 100;
            else if (new_volume < 0.01)
                new_volume = 0;

            music.setVolume(new_volume);
        }

        if (is_clicked(*buttons.at(buttons::play), sf::Mouse::Left, data->window)) {
            // Play button clicked
            data->machine.replace_state(state_ptr(new game_state(data)));
        } else if (is_clicked(*buttons.at(buttons::exit), sf::Mouse::Left, data->window)) {
            // Exit button clicked
            data->window.close();
        } else if (is_clicked(arrows.at(arrows::left), sf::Mouse::Left, data->window)) {
            current_skin_id--;
            if (current_skin_id < 0) current_skin_id = skins_count - 1;

            current_skin_preview = &skins_sprites.at(current_skin_id);

            std::ofstream skin_save_file(CURRENT_SKIN_FILEPATH);

            skin_save_file << skins_filepaths[current_skin_id] << " " << current_skin_id;
        } else if (is_clicked(arrows.at(arrows::right), sf::Mouse::Left, data->window)) {
            current_skin_id++;
            if (current_skin_id == skins_count) current_skin_id = 0;

            current_skin_preview = &skins_sprites.at(current_skin_id);

            std::ofstream skin_save_file(CURRENT_SKIN_FILEPATH);

            skin_save_file << skins_filepaths[current_skin_id] << " " << current_skin_id;
        }
    }
}

void main_menu_state::update(float dt) {}

void main_menu_state::draw(float dt) {
    data->window.clear();

    data->window.draw(bg);

    for (const sf::Sprite* b : buttons) data->window.draw(*b);

    data->window.draw(best_score);

    data->window.draw(*current_skin_preview);

    for (const sf::Sprite& a : arrows) data->window.draw(a);

    data->window.display();
}

void main_menu_state::close() { music.stop(); }
}  // namespace yapg
