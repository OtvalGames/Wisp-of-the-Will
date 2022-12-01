#include "game.hpp"

#include "splash_state.hpp"

namespace bruh {
game::game() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Final: data->window.create(sf::VideoMode().getFullscreenModes().at(0), "YAPG",
    // sf::Style::Fullscreen, settings);
    data->window.create(sf::VideoMode().getFullscreenModes().at(2), "YAPG", sf::Style::Default,
                        settings);
    data->window.setFramerateLimit(144);
    data->window.setPosition(sf::Vector2i(0, 0));
    data->window.setKeyRepeatEnabled(false);

    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Arrow);

    data->window.setMouseCursor(cursor);

    data->machine.add_state(state_ptr(new splash_state(data)));

    run();
}

void game::run() {
    float new_time, frame_time;
    float current_time = clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    const float max_frame_time = 0.25f;

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
}  // namespace bruh
