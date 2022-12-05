#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <SFML/Graphics.hpp>

#define FONT_IMPACT "res/font_impact.ttf"

// Save
#define MAX_SCORE_FILEPATH "res/save/max_score.txt"
#define CURRENT_SKIN_FILEPATH "res/save/current_skin.txt"
#define MUSIC_SETTINGS_FILEPATH "res/save/music_settings.txt"

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
#define ARROW_RIGHT_FILEPATH "res/images/arrow_right.png"
#define ARROW_LEFT_FILEPATH "res/images/arrow_left.png"

// Game objects
#define PLAYER_ANIM_CLASSIC_FILEPATH "res/images/player_anim_classic.png"
#define PLAYER_ANIM_OUTLINE_FILEPATH "res/images/player_anim_outline.png"
#define PLAYER_ANIM_SHARPEN_FILEPATH "res/images/player_anim_sharpen.png"
#define PLAYER_ANIM_FIRE_FILEPATH "res/images/player_anim_fire.png"
#define PLAYER_SKIN_PREVIEW_CLASSIC_FILEPATH "res/images/player_skin_preview_classic.png"
#define PLAYER_SKIN_PREVIEW_OUTLINE_FILEPATH "res/images/player_skin_preview_outline.png"
#define PLAYER_SKIN_PREVIEW_SHARPEN_FILEPATH "res/images/player_skin_preview_sharpen.png"
#define PLAYER_SKIN_PREVIEW_FIRE_FILEPATH "res/images/player_skin_preview_fire.png"
#define WALLS_FILEPATH "res/images/walls.png"
#define OBSTACLES_FILEPATH "res/images/obstacles.png"
#define BONUS_COIN_FILEPATH "res/images/bonus_coin.png"
#define BONUS_SKIP_FILEPATH "res/images/bonus_skip.png"
#define BONUS_SHIELD_FILEPATH "res/images/bonus_shield.png"

// OST
#define OST_HM_DUST_FILEPATH "res/audio/Dust.ogg"
#define OST_HM_HYDROGEN_FILEPATH "res/audio/Hydrogen.ogg"

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
