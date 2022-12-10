#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include <SFML/Audio/Music.hpp>
#include <map>

#include "game.hpp"
#include "state.hpp"

namespace wotw {
constexpr int menu_buttons_count = 2;

class main_menu_state : public state {
   private:
    enum buttons { play = 0, exit };
    enum skins { classic = 0, outline, shapren, fire };
    enum arrows { left = 0, right };

    game_data_ptr data;
    sf::Sprite bg;
    std::deque<sf::Sprite*> buttons;

    sf::Text best_score;
    sf::Font score_font;

    int skins_count = 4;

    std::vector<sf::Sprite> skins_sprites;
    sf::Sprite* current_skin_preview;

    int current_skin_id;

    std::map<int, std::string> skins_filepaths;

    std::vector<sf::Sprite> arrows;

    sf::Music music;

   public:
    main_menu_state(game_data_ptr _data);

    void handle_input();
    void update(float dt);
    void draw(float dt);

    ~main_menu_state();
};
}  // namespace wotw

#endif  // MAIN_MENU_STATE_HPP
