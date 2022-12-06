#include "game.hpp"

#include "splash_state.hpp"

namespace yapg {
game::game() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // data->window.create(sf::VideoMode().getFullscreenModes().at(2), "Wisp of the Will",
    // sf::Style::Default, settings);
    data->window.create(sf::VideoMode().getFullscreenModes().at(0), "Wisp of the Will",
                        sf::Style::Fullscreen, settings);

    data->window.setFramerateLimit(framerate);
    data->window.setPosition(sf::Vector2i(0, 0));
    data->window.setKeyRepeatEnabled(false);

    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Arrow);

    data->window.setMouseCursor(cursor);

    data->machine.add_state(state_ptr(new splash_state(data)));
    run();
}

void game::run() {
    float new_time = 0;
    float frame_time = 0;
    float current_time = clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    constexpr float max_frame_time = 0.25f;

    while (data->window.isOpen()) {
        data->machine.state_change_process();

        new_time = clock.getElapsedTime().asSeconds();
        frame_time = new_time - current_time;

        if (frame_time > max_frame_time) frame_time = max_frame_time;

        current_time = new_time;
        accumulator += frame_time;

        while (accumulator >= dt) {
            data->machine.get_active_state()->handle_input();
            data->machine.get_active_state()->update(dt);
            accumulator -= dt;
        }

        data->machine.get_active_state()->draw(accumulator / dt);
    }
}
}  // namespace yapg
