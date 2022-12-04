#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "game.hpp"
#include "obstacle.hpp"
#include "player.hpp"
#include "state.hpp"
#include "timer.hpp"
#include "walls.hpp"

namespace yapg {
constexpr int bonus_count = 3;

enum bonus { coin = 0, shield, extra_life};

class game_state : public state {
   private:
    game_data_ptr data;
    timer clock;

    player_ player;
    bool bonuses[3];

    walls* _walls;

    sf::Vector2f lines[3];

    std::vector<obstacle> _obstacles;

    float object_spawn_interval;
    float object_spawn_interval_decrease;
    float object_spawn_interval_min;
    float last_object_spawn_time;

    float object_speed;
    float object_speed_increase;
    float object_speed_max;

    float object_speed_increase_interval;
    float last_object_speed_increase_time;
    float object_spawn_interval_decrease_interval;
    float last_object_spawn_interval_decrease_time;

    unsigned int score;
    unsigned int score_increase;
    unsigned int max_score;

    sf::Text bonus_text;
    sf::Text score_text;
    sf::Font score_font;

   private:
    void obstacles_update(float dt);
    void objects_spawn();
    obstacle& get_free_obstacle(std::vector<obstacle>& arr);
    void set_rand_obstacle_texture(obstacle& _obstacle);

    void max_score_save();

    friend obstacle* player_hit_obstacle(game_state& gs);

   public:
    game_state(game_data_ptr _data);

    void init();

    void handle_input();
    void update(float dt);
    void draw(float dt);
};
}  // namespace yapg

#endif  // GAME_STATE_HPP
