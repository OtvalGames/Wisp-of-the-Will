#include "resources.hpp"

#include <fstream>

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

        sf::Vector2i mouse_pos = sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

        if (tmp.contains(mouse_pos)) return true;
    }

    return false;
}

unsigned int get_score_from_save() {
    int score = 0;

    std::ifstream file(MAX_SCORE_FILEPATH);

    if (file.is_open()) {
        std::string str;
        file >> score;

        if (score < 0) score = 0;

        file.close();
    } else {
        std::ofstream file(MAX_SCORE_FILEPATH);

        file << score;

        file.close();
    }

    return score;
}

void write_score_to_save(unsigned int score) {
    std::ofstream file(MAX_SCORE_FILEPATH);

    if (file.is_open()) {
        file << score << std::endl;
    }
}
