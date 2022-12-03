#include "player.hpp"

#include "resources.hpp"

namespace yapg {

player_::player_(game_data_ptr _data) {
    init(_data);
}

void player_::init(game_data_ptr _data) {
    data = _data;

    sf::Image player_animations_image;
    player_animations_image.loadFromFile(PLAYER_ANIMATIONS_FILEPATH);

    constexpr int i = 3;

    for (int j = 0; j < player_sprite_size * frames_count; j += player_sprite_size) {
        sf::Texture tmp;
        tmp.loadFromImage(player_animations_image,
                          sf::IntRect(j, i * player_sprite_size, player_sprite_size, player_sprite_size));

        animations.push_back(tmp);
    }
    direction = direction::stay;

    animation_iterator = 0;
    sprite.setTexture(animations.at(0));

    sprite.setScale(sf::Vector2f(3, 3));
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

void player_::handle_input(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) {
            direction = direction::up;
        }
        else if (event.key.code == sf::Keyboard::S) {
            direction = direction::down;
        }
        else direction = direction::stay;
    }
}

//void player_::movement(float dt) {
//    move((float)vspeed * dt);
//}


void player_::set_speed(unsigned int _speed) { vspeed = _speed; }

unsigned int player_::get_speed() { return vspeed; }

void player_::set_position(sf::Vector2f point) { sprite.setPosition(point); }

sf::Vector2f player_::get_position() { return sprite.getPosition(); }

unsigned int player_::get_direction() { return direction; }

sf::Sprite& player_::get_sprite() { return sprite; }

}  // namespace yapg
