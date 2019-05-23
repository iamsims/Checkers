#ifndef STATE_HPP
#define STATE_HPP


namespace Checkers {
    class State {
    public:
        virtual void init() = 0;

        virtual void handleInput() = 0;
        virtual void update(float dt) = 0;
        virtual void render(float dt) = 0;

        virtual void pause() { }
        virtual void resume() { }
    };
}

#endif
