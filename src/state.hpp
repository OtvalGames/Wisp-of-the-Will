#ifndef STATE_HPP
#define STATE_HPP

namespace bruh {
class state {
   public:
    virtual void init() = 0;

    virtual void handle_input() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(float dt) = 0;
};
}  // namespace bruh

#endif
