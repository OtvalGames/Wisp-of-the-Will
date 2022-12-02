#include "resources.hpp"

//#include <cmath>

void fit_sprite_size(sf::Sprite& object, const sf::Vector2f exp_size) {
    const sf::FloatRect& bounds = object.getGlobalBounds();
    if (exp_size.x != bounds.width) {
        float sx = static_cast<float>(exp_size.x / bounds.width);
        object.setScale(sx, object.getScale().y);
    }
    if (exp_size.y != bounds.height) {
        float sy = static_cast<float>(exp_size.y / bounds.height);
        object.setScale(object.getScale().x, sy);
    }
}

bool is_clicked(sf::Sprite _object, sf::Mouse::Button _button, sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(_button)) {
        sf::IntRect tmp(_object.getPosition().x, _object.getPosition().y,
                        _object.getGlobalBounds().width, _object.getGlobalBounds().height);

        if (tmp.contains(sf::Mouse::getPosition(window))) return true;
    }

    return false;
}

// sf::Vector2f normalize_vector2f(sf::Vector2f vector) {
//     if (vector.x == 0 && vector.y == 0) return vector;

//    float vector_length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
//    vector = sf::Vector2f(vector.x / vector_length, vector.y / vector_length);

//    return vector;
//}

sf::Vector2f tile_pos_to_coords(int pos_x, int pos_y, int tile_size) {
    return sf::Vector2f(pos_x * tile_size + tile_size / 2, pos_y * tile_size + tile_size / 2);
}

// void center_sprite_horizontally(sf::Sprite& object, const sf::Window& win) {
//     float cx = (win.getSize().x / 2) - (object.getGlobalBounds().width / 2);
//     object.setPosition(cx, object.getPosition().y);
// }

// void place_menu_button(sf::Sprite& _logo, sf::Sprite* upper_button, sf::Sprite* current_button) {
//     if (upper_button && current_button) {
//         current_button->setPosition(current_button->getPosition().x, upper_button->getPosition().y +
//         button_height * button_spacing_mul);
//     }
//     else if (current_button) {
//         current_button->setPosition(current_button->getPosition().x, _logo.getPosition().y +
//         logo_height + button_height * 2);
//     }
// }
