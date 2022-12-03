#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <memory>
#include <stack>

#include "state.hpp"

namespace yapg {
typedef std::unique_ptr<state> state_ptr;

class state_machine {
   public:
    void add_state(state_ptr _state);
    void replace_state(state_ptr _state);
    void remove_state();

    void clear_states();

    void state_change_process();

    state_ptr& get_active_state();

   private:
    std::stack<state_ptr> states;

    state_ptr new_state;

    bool is_adding;
    bool is_replacing;
    bool is_removing;
    bool is_clear;
};
}  // namespace yapg

#endif
