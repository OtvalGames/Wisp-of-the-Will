#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <SFML/Audio/Music.hpp>

#include "game.hpp"
#include "obstacle.hpp"
#include "player.hpp"
#include "state.hpp"
#include "timer.hpp"
#include "walls.hpp"

namespace wotw {
class game_state : public state {
   private:
    game_data_ptr data;
    sf::Music music;
    timer clock;

    player_ player;

    bool bonuses[bonus_count];
    sf::Text bonus_text;
    std::deque<sf::Sprite> bonus_sprites;

    timer coin_bonus_timer;

    timer shield_bonus_timer;
    float shield_object_speed_before;

    walls* _walls;

    sf::Vector2f lines[3];

    std::vector<obstacle> _obstacles;

    float object_spawn_interval;
    float last_object_spawn_time;

    float object_speed;

    float last_object_speed_increase_time;
    float last_object_spawn_interval_decrease_time;

    unsigned int score;
    unsigned int max_score;

    sf::Text score_text;
    sf::Font score_font;

    void obstacles_update(float dt);
    void objects_spawn();
    obstacle& get_free_obstacle(std::vector<obstacle>& arr);
    void set_rand_obstacle_texture(obstacle& _obstacle);

    void max_score_save();

    friend obstacle* player_hit_obstacle(game_state& gs);

   public:
    game_state(game_data_ptr _data);

    void handle_input();
    void update(float dt);
    void draw(float dt);

    ~game_state();
};
}  // namespace wotw

#endif  // GAME_STATE_HPP
