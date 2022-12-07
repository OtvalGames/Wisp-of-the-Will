#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>

namespace wotw {
class asset_manager {
   public:
    void load_texture(std::string _name, std::string _file_name);

    sf::Texture& get_texture(std::string _name);

   private:
    std::map<std::string, sf::Texture> textures;
};
}  // namespace wotw

#endif
