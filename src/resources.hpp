#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <SFML/Graphics.hpp>

#define FONT_IMPACT "res/font_impact.ttf"

// Save
#define MAX_SCORE_FILEPATH "res/save/max_score.txt"

// Backgrounds
#define SPLASH_BG_FILEPATH "res/images/og_logo.png"
#define MENU_BG_FILEPATH "res/images/menu_bg.png"
#define PAUSE_BG_FILEPATH MENU_BG_FILEPATH
#define GAMEOVER_BG_FILEPATH MENU_BG_FILEPATH

// Buttons
#define GO_BUTTON_FILEPATH "res/images/button_go.png"
#define PLAY_BUTTON_FILEPATH "res/images/button_play.png"
#define AGAIN_BUTTON_FILEPATH "res/images/button_again.png"
#define EXIT_BUTTON_FILEPATH "res/images/button_exit.png"

// Game objects
#define PLAYER_ANIMATIONS_FILEPATH "res/images/player_animations.png"
#define WALLS_FILEPATH "res/images/walls.png"
#define OBSTACLES_FILEPATH "res/images/obstacles.png"

// Properties
constexpr int player_sprite_size = 16;
constexpr int frames_count = 9;
constexpr float menu_buttons_gap_mul = 1.5;

// Save
unsigned int get_score_from_save();
void write_score_to_save(unsigned int score);

// Sprites
void fit_sprite_size(sf::Sprite& object, const sf::Vector2f exp_size);
bool is_clicked(sf::Sprite _object, sf::Mouse::Button _button, sf::RenderWindow& window);

#endif  // RESOURCES_HPP
