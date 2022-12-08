#include "game_state.hpp"

#include <fstream>

#include "game_over_state.hpp"
#include "pause_state.hpp"
#include "resources.hpp"

namespace wotw {
constexpr int tile_size = 64;
constexpr float object_speed_max = -1100.0;

game_state::game_state(game_data_ptr _data)
    : data(_data),
      player(_data),
      _walls(new walls(_data)),
      object_spawn_interval(2.5f),
      last_object_spawn_time(0.0f),
      object_speed(-200.0f),
      last_object_speed_increase_time(0.0f),
      score(0) {}

void game_state::init() {
    srand(time(NULL));

    data->assets.load_texture("Obstacles", OBSTACLES_FILEPATH);
    data->assets.load_texture("Bonus Coin", BONUS_COIN_FILEPATH);
    data->assets.load_texture("Bonus Skip", BONUS_SKIP_FILEPATH);
    data->assets.load_texture("Bonus Shield", BONUS_SHIELD_FILEPATH);

    player.set_position(
        sf::Vector2f(player.get_position().x - data->window.getSize().x / 4, player.get_position().y));

    for (int i = 0; i < bonus_count; i++) {
        // Create bonus sprites

        sf::Sprite s;
        s.setOrigin(player.get_sprite().getOrigin());

        bonus_sprites.push_back(s);
    }

    bonus_sprites.at(coin).setTexture(data->assets.get_texture("Bonus Coin"));
    bonus_sprites.at(shield).setTexture(data->assets.get_texture("Bonus Shield"));
    bonus_sprites.at(skip).setTexture(data->assets.get_texture("Bonus Skip"));

    bonus_sprites.at(shield).setColor(sf::Color(196, 208, 233, 255 / 1.5));
    bonus_sprites.at(skip).setColor(sf::Color(144, 114, 171, 255 / 1.5));

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

    last_object_spawn_interval_decrease_time = 0.0f;
    max_score = get_score_from_save();

    score_font.loadFromFile(FONT_IMPACT);

    score_text.setFont(score_font);
    score_text.setCharacterSize(35);
    score_text.setPosition(data->window.getView().getCenter() - data->window.getView().getSize() / 2.0f +
                           sf::Vector2f(10, 10));
    score_text.setString("Score: 0");

    bonus_text.setFont(*score_text.getFont());
    bonus_text.setCharacterSize(score_text.getCharacterSize());
    bonus_text.setPosition(
        score_text.getPosition().x,
        score_text.getPosition().y + score_text.getGlobalBounds().height * menu_buttons_gap_mul);

    data->window.setMouseCursorVisible(false);

    // Soundtrack
    constexpr float default_volume = 25;

    std::ifstream music_settings(MUSIC_SETTINGS_FILEPATH);

    if (music_settings.is_open()) {
        std::string music_status;

        music_settings >> music_status;

        if (!music_status.compare("on")) {
            music.setLoop(true);
            music.setVolume(default_volume);

            if (music.openFromFile(OST_HM_HYDROGEN_FILEPATH)) music.play();
        }

        music_settings.close();

    } else {
        std::ofstream music_settings(MUSIC_SETTINGS_FILEPATH);

        music_settings << "on";

        music_settings.close();
    }
}

void game_state::handle_input() {
    sf::Event e;

    while (data->window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            max_score_save();
            data->window.close();
        }

        if (e.type == sf::Event::MouseWheelScrolled) {
            // Change music volume by scrolling mouse wheel

            float new_volume = music.getVolume() + e.mouseWheelScroll.delta;

            if (new_volume - 100 > 0.01)
                new_volume = 100;
            else if (new_volume < 0.01)
                new_volume = 0;

            music.setVolume(new_volume);
        }

        if (e.type == sf::Event::KeyPressed) {
            typedef sf::Keyboard kb;

            if (e.key.code == kb::Escape) {
                max_score_save();
                data->machine.add_state(state_ptr(new pause_state(data, &clock)));
            } else if (e.key.code == kb::W || e.key.code == kb::Z) {
                // Move 1 line up
                if (player.get_position().y >= 0) player.get_sprite().move(0, 0 - tile_size);
            } else if (e.key.code == kb::S || e.key.code == kb::X) {
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

        unsigned int r = rand() % bonus_count;
        tmp.set_bonus_type(static_cast<enum bonus>(r));

        std::string text_name("Bonus");

        switch (r) {
            case skip:
                text_name += " Skip";
                break;
            case shield:
                text_name += " Shield";
                break;
            default:
                // case coin:
                text_name += " Coin";
                break;
        }

        tmp.set_texture(data->assets.get_texture(text_name));
        tmp.set_texture_rect(sf::IntRect(0, 0, tile_size, tile_size));
    }
}

void game_state::max_score_save() {
    if (score > max_score) write_score_to_save(score);
}

void game_state::obstacles_update(float dt) {
    constexpr float object_spawn_interval_decrease = 0.1;
    constexpr float object_spawn_interval_min = 0.5;
    constexpr float object_spawn_interval_decrease_interval = 5.0;

    constexpr float object_speed_increase = -5.0;
    constexpr float object_speed_increase_interval = 0.4;

    constexpr int score_increase = 10;

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

    for (sf::Sprite& sprite : bonus_sprites) {
        sprite.setPosition(player.get_position().x - player.get_sprite().getGlobalBounds().width / 2,
                           player.get_position().y - player.get_sprite().getGlobalBounds().height / 2);
    }

    obstacle* hit_obstacle = player_hit_obstacle(*this);

    // Apply shield bonus
    if (bonuses[skip]) {
        // NULL means player does not hit any obstacles
        hit_obstacle = NULL;

        if (shield_bonus_time - shield_bonus_timer.get_elapsed_seconds() > shield_bonus_time / 4) {
            /* Active state of shield bonus:
             * max move speed
             * skip all obstacles */

            object_speed = object_speed_max * 2;
        } else if (shield_bonus_time - shield_bonus_timer.get_elapsed_seconds() > 0.01) {
            /* Before-end state of shield bonus:
             * restore old move speed
             * skip all obstacles */

            object_speed = shield_object_speed_before;
            _walls->set_move_speed(shield_object_speed_before);
        } else {
            // End shield bonus

            shield_bonus_timer.pause();
            bonuses[skip] = false;
        }
    }

    bonus_text.setString("");

    // Show coin bonus message
    if (bonuses[coin] && coin_bonus_show_time - coin_bonus_timer.get_elapsed_seconds() > 0.01) {
        bonus_text.setString("+ 20 Score");
    } else if (bonuses[coin]) {
        /* The message was shown for 3 seconds, so
         * the bonus effect has ended */

        coin_bonus_timer.pause();
        bonuses[coin] = false;
    }

    if (hit_obstacle) {
        // Player hit an obstacle

        if (hit_obstacle->bonus()) {
            // Player got bonus
            enum bonus bt = hit_obstacle->get_bonus_type();

            bonuses[bt] = true;

            if (bt == coin) {
                score += 20;
                coin_bonus_timer.restart();
            } else if (bt == skip) {
                shield_object_speed_before = object_speed;

                shield_bonus_timer.restart();
            }

            hit_obstacle->set_bonus(false);
            return;
        }

        if (bonuses[shield]) {
            // Player had extra life bonus

            bonuses[shield] = false;
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

    for (int i = 1; i < bonus_count; i++) {
        if (bonuses[i]) data->window.draw(bonus_sprites.at(i));
    }

    data->window.display();
}

game_state::~game_state() { music.stop(); }
}  // namespace wotw
