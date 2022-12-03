#include "player.hpp"

#include "resources.hpp"

namespace yapg {

player::player(game_data_ptr _data) {
    init(_data);
}

void player::init(game_data_ptr _data) {
    data = _data;

    animations = new std::vector<sf::Texture>[4];

    sf::Image player_animations_image;
    player_animations_image.loadFromFile(PLAYER_ANIMATIONS_FILEPATH);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < player_sprite_size * frames_count; j += player_sprite_size) {
            sf::Texture tmp;
            tmp.loadFromImage(
                player_animations_image,
                sf::IntRect(j, i * player_sprite_size, player_sprite_size, player_sprite_size));

            animations[i].push_back(tmp);
        }
    }

    animation_iterator = 0;

    direction = direction::stay;

    sprite.setScale(sf::Vector2f(3, 3));
    sprite.setTexture(animations[direction].at(animation_iterator));
    sprite.setOrigin(
        sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2));
}

void player::animate() {
    constexpr float animation_frames_interval = 0.125;
    constexpr int right_animation_index = 3;

    sprite.setTexture(animations[right_animation_index].at(animation_iterator));

    if (clock.getElapsedTime().asSeconds() > animation_frames_interval) {
        animation_iterator++;
        if (animation_iterator == animations[right_animation_index].size()) animation_iterator = 0;

        sprite.setTexture(animations[right_animation_index].at(animation_iterator));

        clock.restart();
    }
}

void player::draw() {
    data->window.draw(sprite);
}

void player::handle_input(sf::Event event) {
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

//void player::movement(float dt) {
//    move((float)vspeed * dt);
//}


void player::set_speed(unsigned int _speed) { vspeed = _speed; }

unsigned int player::get_speed() { return vspeed; }

void player::set_position(sf::Vector2f point) { sprite.setPosition(point); }

sf::Vector2f player::get_position() { return sprite.getPosition(); }

unsigned int player::get_direction() { return direction; }

sf::Sprite& player::get_sprite() { return sprite; }

}  // namespace yapg
