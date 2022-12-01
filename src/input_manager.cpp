#include "input_manager.hpp"

namespace bruh {
sf::Vector2i input_manager::get_mouse_pos(sf::RenderWindow& window) {
    return sf::Mouse::getPosition(window);
}

bool input_manager::is_clicked(sf::Sprite _object, sf::Mouse::Button _button, sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(_button)) {
        sf::IntRect tmp(_object.getPosition().x, _object.getPosition().y,
                        _object.getGlobalBounds().width, _object.getGlobalBounds().height);

        if (tmp.contains(get_mouse_pos(window))) return true;
    }

    return false;
}
}  // namespace bruh
