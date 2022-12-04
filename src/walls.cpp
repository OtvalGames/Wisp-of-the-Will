#include "walls.hpp"

#include "resources.hpp"

namespace yapg {
walls::walls(game_data_ptr _data) : data(_data), move_speed(-200.0f) {
    data->assets.load_texture("Walls", WALLS_FILEPATH);

    sf::Sprite sprite;

    sprite.setTexture(data->assets.get_texture("Walls"));

    sprites.push_back(sprite);
    sprites.push_back(sprite);

    sprites.at(0).setPosition(0 - sprites.at(0).getGlobalBounds().width / 2,
                              0 - sprites.at(0).getGlobalBounds().height / 2);
    sprites.at(1).setPosition(0 + sprites.at(0).getGlobalBounds().width / 2,
                              0 - sprites.at(1).getGlobalBounds().height / 2);
}

void walls::move(float dt) {
    for (int i = 0; i < sprites.size(); i++) {
        sprites.at(i).move(sf::Vector2f(1, 0) * (move_speed * dt));

        if (sprites.at(i).getGlobalBounds().left + sprites.at(i).getGlobalBounds().width <
            data->window.getView().getCenter().x - data->window.getView().getSize().x / 2) {
            int j = (i + 1) % 2;

            sprites.at(i).setPosition(sprites.at(j).getGlobalBounds().left +
                                          sprites.at(j).getGlobalBounds().width + (move_speed * dt),
                                      sprites.at(i).getPosition().y);
        }
    }
}

void walls::draw() {
    for (int i = 0; i < sprites.size(); i++) {
        data->window.draw(sprites.at(i));
    }
}

void walls::set_move_speed(float _speed) { move_speed = _speed; }

int walls::get_move_speed() { return move_speed; }

}  // namespace yapg
