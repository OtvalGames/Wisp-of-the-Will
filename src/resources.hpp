#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <SFML/Graphics.hpp>

#define LOGO_FILEPATH "res/images/og_logo.png"
#define MAX_SCORE_FILEPATH "res/save/max_score.txt"
//#define PLAYER_HP_BAR_FRAME "res/images/player_hp_frame.png"
//#define PLAYER_HP_BAR_LINE "res/images/player_hp_line.png"
//#define EXP_FRAME "res/images/exp_bar_frame.png"
//#define EXP_LINE "res/images/exp_bar_line.png"
//#define CRYSTAL_FILEPATH "res/images/crystal1.png"
#define FONT_IMPACT "res/font_impact.ttf"
//#define FONT_ALEGREYA "res/font_alegreya.ttf"

// Menu
#define MENU_BG_FILEPATH "res/images/menu_bg.png"

// Buttons
#define GO_BUTTON_FILEPATH "res/images/button_go.png"
#define PLAY_BUTTON_FILEPATH "res/images/button_play.png"
#define STAT_BUTTON_FILEPATH "res/images/button_stat.png"
#define EXIT_BUTTON_FILEPATH "res/images/button_exit.png"

// Splash state
#define SPLASH_BG_FILEPATH LOGO_FILEPATH

// Pause state
#define PAUSE_BG_FILEPATH MENU_BG_FILEPATH

// Main menu state
//#define MAIN_MENU_LVL_FILEPATH "res/levels/level_main_menu.txt"
//#define BONUS_HEALTH "res/images/bonus_health.png"
//#define BONUS_SPEED "res/images/bonus_speed.png"
//#define BONUS_ARMOR "res/images/bonus_armor.png"

//#define PLAYER_ANIMATIONS_FILEPATH "res/images/player_animations.png"
//#define PLAYER_SPHERE_FILEPATH "res/images/player_sphere.png"
//#define PLAYER_WISP_FILEPATH "res/images/player_wisp.png"

//#define ENEMY_ANIMATIONS_FILEPATH "res/images/enemy_animations.png"

// Game state
#define GAME_LVL_FILEPATH "res/levels/level_game.txt"
#define WALLS_FILEPATH "res/images/walls.png"
#define OBSTACLES_FILEPATH "res/images/obstacles.png"

// Properties
constexpr int player_sprite_size = 16;
constexpr int frames_count = 9;

// constexpr float logo_width = 300;
// constexpr float logo_height = 170;

// constexpr float button_width = 150;
// constexpr float button_height = 60;
// constexpr float button_spacing_mul = 1.2;

// Resources processing
void fit_sprite_size(sf::Sprite& object, const sf::Vector2f exp_size);
bool is_clicked(sf::Sprite _object, sf::Mouse::Button _button, sf::RenderWindow& window);
// sf::Vector2f normalize_vector2f(sf::Vector2f vector);
sf::Vector2f tile_pos_to_coords(int pos_x, int pos_y, int tile_size);
// void center_sprite_horizontally(sf::Sprite& object, const sf::Window& win);
// void place_menu_button(sf::Sprite& _logo, sf::Sprite* upper_button, sf::Sprite* current_button);

// Save
unsigned int get_score_from_save();
void write_score_to_save(unsigned int score);

#endif  // RESOURCES_HPP
