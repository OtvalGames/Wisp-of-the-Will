#include "asset_manager.hpp"

namespace yapg {
void asset_manager::load_texture(std::string _name, std::string _file_name) {
    sf::Texture txtr;

    if (txtr.loadFromFile(_file_name)) textures[_name] = txtr;
}

void asset_manager::load_texture(std::string _name, std::string _file_name, sf::IntRect _texture_rect) {
    sf::Texture txtr;

    if (txtr.loadFromFile(_file_name, _texture_rect)) textures[_name] = txtr;
}

sf::Texture& asset_manager::get_texture(std::string _name) { return textures.at(_name); }
}  // namespace yapg
