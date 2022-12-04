#include "game_state.hpp"

#include "game_over_state.hpp"
#include "pause_state.hpp"
#include "resources.hpp"

namespace yapg {
constexpr int tile_size = 64;

game_state::game_state(game_data_ptr _data) : data(_data), player(_data) {}

void game_state::init() {
    srand(time(NULL));

    data->assets.load_texture("Obstacles", OBSTACLES_FILEPATH);
    data->assets.load_texture("Bonus", BONUS_FILEPATH);

    _walls = new walls(data);

    player.set_position(
        sf::Vector2f(player.get_position().x - data->window.getSize().x / 4, player.get_position().y));

    // All bonuses is disabled by default
    for (int i = 0; i < bonus_count; i++) bonuses[i] = false;

    constexpr int obstacles_pool_count = 20;

    for (int i = 0; i < obstacles_pool_count; i++) {
        obstacle obst(data);

        _obstacles.push_back(obst);
    }

    sf::View view;
    view.setCenter(0, 0);
    view.setSize(data->window.getSize().x, data->window.getSize().y);

    data->window.setView(view);

    lines[0].x = data->window.getView().getCenter().x + data->window.getView().getSize().x / 2.0f;
    lines[0].y = data->window.getView().getCenter().y - tile_size / 2 - tile_size;
    lines[1].x = data->window.getView().getCenter().x + data->window.getView().getSize().x / 2.0f;
    lines[1].y = data->window.getView().getCenter().y - tile_size / 2;
    lines[2].x = data->window.getView().getCenter().x + data->window.getView().getSize().x / 2.0f;
    lines[2].y = data->window.getView().getCenter().y + tile_size / 2;

    object_spawn_interval = 2.5f;
    object_spawn_interval_decrease = 0.1f;
    object_spawn_interval_min = 0.5f;
    last_object_spawn_time = 0.0f;

    object_speed = -200.0f;
    object_speed_increase = -5.0f;
    object_speed_max = -900.0f;

    object_speed_increase_interval = 0.4f;
    last_object_speed_increase_time = 0.0f;
    object_spawn_interval_decrease_interval = 5.0f;
    last_object_spawn_interval_decrease_time = 0.0f;

    score = 0;
    score_increase = 10;
    max_score = get_score_from_save();

    score_font.loadFromFile(FONT_IMPACT);

    score_text.setFont(score_font);
    score_text.setCharacterSize(35);
    score_text.setPosition(data->window.getView().getCenter() - data->window.getView().getSize() / 2.0f +
                           sf::Vector2f(10, 10));
    score_text.setString("Score: 0");

    bonus_text.setFont(*score_text.getFont());
    bonus_text.setCharacterSize(score_text.getCharacterSize());
    bonus_text.setPosition(score_text.getPosition().x,
                           score_text.getPosition().y + score_text.getGlobalBounds().height * menu_buttons_gap_mul);

    data->window.setMouseCursorVisible(false);
}

void game_state::handle_input() {
    sf::Event e;

    while (data->window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            max_score_save();
            data->window.close();
        }

        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Escape) {
                max_score_save();
                data->machine.add_state(state_ptr(new pause_state(data, &clock)));
            } else if (e.key.code == sf::Keyboard::W) {
                // Move 1 line up
                if (player.get_position().y >= 0) player.get_sprite().move(0, 0 - tile_size);
            } else if (e.key.code == sf::Keyboard::S) {
                // Move 1 line down
                if (player.get_position().y <= 0) player.get_sprite().move(0, tile_size);
            }
        }
    }
}

void game_state::set_rand_obstacle_texture(obstacle& _obstacle) {
    _obstacle.set_texture(data->assets.get_texture("Obstacles"));
    _obstacle.set_texture_rect(sf::IntRect((rand() % 6) * tile_size, 0, tile_size, tile_size));
}

obstacle& game_state::get_free_obstacle(std::vector<obstacle>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        if (!arr.at(i).active()) return arr.at(i);
    }

    return arr.at(0);
}

void game_state::objects_spawn() {
    unsigned int chance = rand() % (100 - 1) + 1;

    if (chance > 0 && chance <= 15) {
        obstacle& tmp = get_free_obstacle(_obstacles);

        tmp.activate();
        tmp.set_position(lines[0]);
        set_rand_obstacle_texture(tmp);
    } else if (chance > 15 && chance <= 30) {
        obstacle& tmp = get_free_obstacle(_obstacles);

        tmp.activate();
        tmp.set_position(lines[1]);
        set_rand_obstacle_texture(tmp);
    } else if (chance > 30 && chance <= 45) {
        obstacle& tmp = get_free_obstacle(_obstacles);

        tmp.activate();
        tmp.set_position(lines[2]);
        set_rand_obstacle_texture(tmp);
    } else if (chance > 45 && chance <= 60) {
        obstacle& tmp1 = get_free_obstacle(_obstacles);

        tmp1.activate();
        tmp1.set_position(lines[0]);
        set_rand_obstacle_texture(tmp1);

        obstacle& tmp2 = get_free_obstacle(_obstacles);

        tmp2.activate();
        tmp2.set_position(lines[1]);
        set_rand_obstacle_texture(tmp2);
    } else if (chance > 60 && chance <= 75) {
        obstacle& tmp1 = get_free_obstacle(_obstacles);

        tmp1.activate();
        tmp1.set_position(lines[1]);
        set_rand_obstacle_texture(tmp1);

        obstacle& tmp2 = get_free_obstacle(_obstacles);

        tmp2.activate();
        tmp2.set_position(lines[2]);
        set_rand_obstacle_texture(tmp2);
    } else if (chance > 75 && chance <= 90) {
        obstacle& tmp1 = get_free_obstacle(_obstacles);

        tmp1.activate();
        tmp1.set_position(lines[0]);
        set_rand_obstacle_texture(tmp1);

        obstacle& tmp2 = get_free_obstacle(_obstacles);

        tmp2.activate();
        tmp2.set_position(lines[2]);
        set_rand_obstacle_texture(tmp2);
    } else {
        // Spawn bonus

        obstacle& tmp = get_free_obstacle(_obstacles);

        tmp.activate();
        tmp.set_bonus(true);
        tmp.set_position(lines[1]);

        tmp.set_texture(data->assets.get_texture("Bonus"));
        tmp.set_texture_rect(sf::IntRect(0, 0, tile_size, tile_size));
    }
}

void game_state::max_score_save() {
    if (score > max_score) write_score_to_save(score);
}

void game_state::obstacles_update(float dt) {
    if (clock.get_elapsed_seconds() - last_object_spawn_time >= object_spawn_interval) {
        objects_spawn();
        last_object_spawn_time = clock.get_elapsed_seconds();
    }

    if (clock.get_elapsed_seconds() - last_object_spawn_interval_decrease_time >=
        object_spawn_interval_decrease_interval) {
        if (object_spawn_interval > object_spawn_interval_min) {
            object_spawn_interval -= object_spawn_interval_decrease;
            last_object_spawn_interval_decrease_time = clock.get_elapsed_seconds();
        }
    }

    if (clock.get_elapsed_seconds() - last_object_speed_increase_time >=
        object_speed_increase_interval) {
        if (std::abs(object_speed) < std::abs(object_speed_max)) {
            object_speed += object_speed_increase;
            _walls->set_move_speed(object_speed);
            last_object_speed_increase_time = clock.get_elapsed_seconds();
        }
    }

    for (obstacle& obstacle : _obstacles) {
        if (!obstacle.active()) {
            obstacle.set_bonus(false);
            continue;
        }

        obstacle.move(sf::Vector2f(1, 0) * (object_speed * dt));

        if (obstacle.get_global_bounds().left + obstacle.get_global_bounds().width <
            data->window.getView().getCenter().x - data->window.getView().getSize().x / 2) {
            obstacle.disable();
            obstacle.set_bonus(false);

            score += score_increase;
            score_text.setString("Score: " + std::to_string(score));
        }
    }
}

obstacle* player_hit_obstacle(game_state& gs) {
    sf::Sprite player_sprite = gs.player.get_sprite();

    for (obstacle& obstacle : gs._obstacles) {
        if (!obstacle.active()) continue;

        if (player_sprite.getGlobalBounds().intersects(obstacle.get_global_bounds())) {
            obstacle.disable();

            return &obstacle;
        }
    }

    return NULL;
}

void game_state::update(float dt) {
    constexpr float coin_bonus_show_time = 3.0;
    constexpr float shield_bonus_time = 6.0;

    _walls->move(dt);
    obstacles_update(dt);

    obstacle* hit_obstacle = player_hit_obstacle(*this);

    // Apply shield bonus
    if (bonuses[bonus::shield]) {
        // NULL means player does not hit any obstacles
        hit_obstacle = NULL;

        if (shield_bonus_time - shield_bonus_timer.get_elapsed_seconds() > shield_bonus_time / 4) {
            /* Active state of shield bonus:
             * max move speed
             * skip all obstacles */

            object_speed = object_speed_max * 2;
        }
        else if (shield_bonus_time - shield_bonus_timer.get_elapsed_seconds() > 0.01) {
            /* Before-end state of shield bonus:
             * restore old move speed
             * skip all obstacles */

            object_speed = shield_object_speed_before;
        }
        else {
            // End shield bonus

            shield_bonus_timer.pause();
            bonuses[bonus::shield] = false;
        }

        bonus_text.setString("Shield");
    }
    else bonus_text.setString("");

    // Apply extra life bonus
    if (bonuses[bonus::extra_life]) {
        if (bonus_text.getString().isEmpty())
            bonus_text.setString(bonus_text.getString() + "Extra life");
        else
            bonus_text.setString(bonus_text.getString() + "\nExtra life");
    }

    // Apply coin bonus
    if (bonuses[bonus::coin] && coin_bonus_show_time - coin_bonus_timer.get_elapsed_seconds() > 0.01) {
        if (bonus_text.getString().isEmpty())
            bonus_text.setString(bonus_text.getString() + "+ 20 Score");
        else
            bonus_text.setString(bonus_text.getString() + "\n+ 20 Score");
    } else if (bonuses[bonus::coin]) {
        /* The message was shown for 3 seconds, so
         * the bonus effect has ended */

        coin_bonus_timer.pause();
        bonuses[bonus::coin] = false;
    }

    if (hit_obstacle) {
        // Player hit an obstacle

        if (hit_obstacle->bonus()) {
            // Player got random bonus
            unsigned int r = rand() % bonus_count;

            bonuses[r] = true;

            if (r == bonus::coin) {
                score += 20;
                coin_bonus_timer.restart();
            }
            else if (r == bonus::shield) {
                shield_object_speed_before = object_speed;

                shield_bonus_timer.restart();
            }

            hit_obstacle->set_bonus(false);
            return;
        }

        if (bonuses[bonus::extra_life]) {
            // Player had extra life bonus

            bonuses[bonus::extra_life] = false;
        } else {
            // Player died

            max_score_save();
            data->machine.replace_state(state_ptr(new game_over_state(data, score, clock)));
        }
    }
}

void game_state::draw(float dt) {
    data->window.clear(sf::Color(0, 5, 25));

    _walls->draw();

    for (obstacle& obstacle : _obstacles)
        if (obstacle.active()) obstacle.draw();

    player.draw();
    data->window.draw(score_text);
    data->window.draw(bonus_text);

    data->window.display();
}
}  // namespace yapg
