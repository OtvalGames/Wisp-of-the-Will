#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <SFML/Graphics.hpp>

namespace yapg {
class input_manager {
   public:
    sf::Vector2i get_mouse_pos(sf::RenderWindow& window);

    bool is_clicked(sf::Sprite _object, sf::Mouse::Button _button, sf::RenderWindow& window);
};
}  // namespace yapg

#endif
