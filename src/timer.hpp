#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/System/Clock.hpp>

namespace yapg {
class timer {
   private:
    sf::Clock sf_timer;
    float run_time;

    bool paused;

   public:
    timer() : run_time(0), paused(false) { sf_timer.restart(); }

    void start() {
        if (paused) {
            sf_timer.restart();
            paused = false;
        }
    }

    void restart() {
        run_time = 0;
        sf_timer.restart();

        paused = false;
    }

    void pause() {
        if (!paused) {
            run_time += sf_timer.getElapsedTime().asSeconds();
            paused = true;
        }
    }

    float get_elapsed_seconds() {
        if (!paused) return run_time + sf_timer.getElapsedTime().asSeconds();

        return run_time;
    }
};
}  // namespace yapg

#endif  // TIMER_HPP
