#ifndef STATE_HPP
#define STATE_HPP

namespace yapg {
class state {
   public:
    virtual void init() = 0;

    virtual void handle_input() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(float dt) = 0;
    virtual void close() = 0;
};
}  // namespace yapg

#endif
