#include "game_state.hpp"

#include "pause_state.hpp"
#include "resources.hpp"

namespace yapg {
game_state::game_state(game_data_ptr _data) : data(_data) {}

void game_state::init() {
    srand(time(NULL));

    data->assets.load_texture("Obstacles", OBSTACLES_FILEPATH);

    _walls = new walls(data);

    int obstacles_pool_count = 10;

    for (int i = 0; i < obstacles_pool_count; i++) {
        obstacle obst(data);

        _obstacles.push_back(obst);
    }

    sf::View view;
    view.setCenter(0, 0);
    view.setSize(data->window.getSize().x, data->window.getSize().y);

    data->window.setView(view);

    lines[0].x = data->window.getView().getCenter().x + data->window.getView().getSize().x / 2.0f;
    lines[0].y = data->window.getView().getCenter().y - 32 - 64;
    lines[1].x = data->window.getView().getCenter().x + data->window.getView().getSize().x / 2.0f;
    lines[1].y = data->window.getView().getCenter().y - 32;
    lines[2].x = data->window.getView().getCenter().x + data->window.getView().getSize().x / 2.0f;
    lines[2].y = data->window.getView().getCenter().y + 32;

    object_spawn_interval = 2.5f;
    object_spawn_interval_decrease = 0.05f;
    object_spawn_interval_min = 0.5f;
    last_object_spawn_time = 0.0f;

    object_speed = -200.0f;
    object_speed_increase = -5.0f;
    object_speed_max = -700.0f;

    object_speed_increase_interval = 1.0f;
    last_object_speed_increase_time = 0.0f;
    object_spawn_interval_decrease_interval = 5.0f;
    last_object_spawn_interval_decrease_time = 0.0f;

    score = 0;
    score_increase = 10;
    max_score = get_score_from_save();

    score_font.loadFromFile(FONT_IMPACT);

    score_text.setFont(score_font);
    score_text.setCharacterSize(35);
    score_text.setPosition(data->window.getView().getCenter() - data->window.getView().getSize() / 2.0f + sf::Vector2f(10, 10));
    score_text.setString("Score: 0");
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
                data->machine.add_state(state_ptr(new pause_state(data)));
            }
        }
    }
}

void game_state::set_rand_obstacle_texture(obstacle& _obstacle) {
    _obstacle.set_texture(data->assets.get_texture("Obstacles"));
    _obstacle.set_texture_rect(sf::IntRect((rand() % 4) * 64, 0, 64, 64));
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
        // spawn bonus bobonus
    }
}

void game_state::max_score_save() {
    if (score > max_score) write_score_to_save(score);
}

void game_state::obstacles_update(float dt) {
    if (clock.getElapsedTime().asSeconds() - last_object_spawn_time >= object_spawn_interval) {
        objects_spawn();
        last_object_spawn_time = clock.getElapsedTime().asSeconds();
    }

    if (clock.getElapsedTime().asSeconds() - last_object_spawn_interval_decrease_time >=
        object_spawn_interval_decrease_interval) {
        if (object_spawn_interval > object_spawn_interval_min) {
            object_spawn_interval -= object_spawn_interval_decrease;
            last_object_spawn_interval_decrease_time = clock.getElapsedTime().asSeconds();
        }
    }

    if (clock.getElapsedTime().asSeconds() - last_object_speed_increase_time >=
        object_speed_increase_interval) {
        if (std::abs(object_speed) < std::abs(object_speed_max)) {
            object_speed += object_speed_increase;
            _walls->set_move_speed(object_speed);
            last_object_speed_increase_time = clock.getElapsedTime().asSeconds();
        }
    }

    for (int i = 0; i < _obstacles.size(); i++) {
        if (_obstacles.at(i).active()) {
            _obstacles.at(i).move(sf::Vector2f(1, 0) * (object_speed * dt));

            if (_obstacles.at(i).get_global_bounds().left + _obstacles.at(i).get_global_bounds().width <
                data->window.getView().getCenter().x - data->window.getView().getSize().x / 2) {
                _obstacles.at(i).disable();
                score += score_increase;
                score_text.setString("Score: " + std::to_string(score));
            }
        }
    }
}

void game_state::update(float dt) {
    _walls->move(dt);
    obstacles_update(dt);
    // if (player_death) if (score > max_score) save_max_score();
}

void game_state::draw(float dt) {
    data->window.clear(sf::Color(0, 5, 25));

    _walls->draw();

    for (int i = 0; i < _obstacles.size(); i++)
        if (_obstacles.at(i).active()) _obstacles.at(i).draw();

    data->window.draw(score_text);

    data->window.display();
}
}  // namespace yapg
