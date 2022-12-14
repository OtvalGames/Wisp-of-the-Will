#include "player.hpp"

#include <fstream>

#include "resources.hpp"

namespace wotw {
player_::player_(game_data_ptr _data) : data(_data), animation_iterator(0) {
    std::string animations_filepath = PLAYER_ANIM_CLASSIC_FILEPATH;

    std::ifstream current_skin_file(CURRENT_SKIN_FILEPATH);

    if (current_skin_file.is_open()) {
        current_skin_file >> animations_filepath;

        current_skin_file.close();
    }

    sf::Image player_animations_image;
    player_animations_image.loadFromFile(animations_filepath);

    for (int i = 0; i < player_sprite_size * frames_count; i += player_sprite_size) {
        sf::Texture texture;
        texture.loadFromImage(player_animations_image,
                              sf::IntRect(i, 0, player_sprite_size, player_sprite_size));

        animations.push_back(texture);
    }

    sprite.setTexture(animations.at(animation_iterator));

    sprite.setScale(3, 3);
    sprite.setOrigin(
        sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2));
}

void player_::animate() {
    constexpr float animation_frames_interval = 0.125;

    sprite.setTexture(animations.at(animation_iterator));

    if (clock.getElapsedTime().asSeconds() > animation_frames_interval) {
        animation_iterator++;

        if (animation_iterator == animations.size()) animation_iterator = 0;

        sprite.setTexture(animations.at(animation_iterator));

        clock.restart();
    }
}

void player_::draw() {
    animate();
    data->window.draw(sprite);
}

void player_::set_position(sf::Vector2f point) { sprite.setPosition(point); }

sf::Vector2f player_::get_position() { return sprite.getPosition(); }

sf::Sprite& player_::get_sprite() { return sprite; }

}  // namespace wotw
