#include "state_machine.hpp"

namespace wotw {
void state_machine::add_state(state_ptr _state) {
    is_adding = true;

    new_state = std::move(_state);
}

void state_machine::replace_state(state_ptr _state) {
    is_replacing = true;

    new_state = std::move(_state);
}

void state_machine::remove_state() { is_removing = true; }

void state_machine::clear_states() { is_clear = true; }

void state_machine::state_change_process() {
    if (is_removing) {
        if (!states.empty()) {
            states.top()->close();
            states.pop();
        }

        is_removing = false;
    } else if (is_clear) {
        while (!states.empty()) {
            states.top()->close();
            states.pop();
        }

        is_clear = false;
    }

    if (is_adding) {
        states.push(std::move(new_state));
        states.top()->init();

        is_adding = false;
    } else if (is_replacing) {
        if (!states.empty()) {
            states.top()->close();
            states.pop();
            states.push(std::move(new_state));
            states.top()->init();
        }

        is_replacing = false;
    }
}

state_ptr& state_machine::get_active_state() { return states.top(); }
}  // namespace wotw
