#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>

namespace yapg {
class level {
   public:
    level();

    void load_level(std::string file_name);
    void delete_solid_objects();

    void draw(sf::RenderWindow& window);

    void set_tile_size(unsigned int width, unsigned int height);

    std::vector<sf::Sprite>& get_objects();

    sf::Vector2u get_level_size();
    sf::Vector2u get_tile_size();

   private:
    std::vector<std::string> tilemap;

    std::map<char, sf::Texture> textures;

    std::vector<sf::Sprite> objects;

    unsigned int level_width, level_height, tile_width, tile_height;
};
}  // namespace yapg

#endif
