#include "level.hpp"

#include <fstream>

namespace yapg {
level::level() {
    tile_width = 64;
    tile_height = 64;

    level_width = 0;
    level_height = 0;
}

void level::load_level(std::string file_name) {
    std::ifstream file(file_name);

    if (!file.is_open()) return;

    std::string tiles_image_path;
    file >> tiles_image_path;

    sf::Image tiles_image;
    tiles_image.loadFromFile(tiles_image_path);

    while (1) {
        std::string symbol;
        sf::IntRect coords;

        file >> symbol;
        if (symbol.compare("level") == 0) break;

        file >> coords.left;
        file >> coords.top;

        coords.width = coords.left + tile_width;
        coords.height = coords.top + tile_height;

        sf::Texture texture;

        texture.loadFromImage(tiles_image, coords);

        textures[symbol[0]] = texture;
    }

    std::string buf;

    while (!file.eof()) {
        file >> buf;

        if (buf.compare("end") == 0) break;

        tilemap.push_back(buf);

        if (tilemap[level_height].length() > level_width) level_width = tilemap[level_height].length();

        for (int i = 0; i < tilemap[level_height].length(); i++) {
            sf::Sprite obj;
            sf::Texture txtr;

            obj.setTexture(textures[tilemap[level_height][i]]);
            obj.setTextureRect(sf::IntRect(0, 0, 64, 64));
            obj.setPosition(sf::Vector2f(i * tile_width, level_height * tile_height));

            objects.push_back(obj);
        }

        level_height++;
    }
}

void level::set_tile_size(unsigned int _width, unsigned int _height) {
    tile_width = _width;
    tile_height = _height;
}

std::vector<sf::Sprite>& level::get_objects() { return objects; }

void level::draw(sf::RenderWindow& window) {
    for (int i = 0; i < objects.size(); i++) window.draw(objects[i]);
}

sf::Vector2u level::get_level_size() { return sf::Vector2u(level_width, level_height); }

sf::Vector2u level::get_tile_size() { return sf::Vector2u(tile_width, tile_height); }
}  // namespace yapg
