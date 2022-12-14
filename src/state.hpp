#ifndef STATE_HPP
#define STATE_HPP

namespace wotw {
class state {
   public:
    state() = default;

    virtual void handle_input() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(float dt) = 0;

    virtual ~state() = default;
};
}  // namespace wotw

#endif
