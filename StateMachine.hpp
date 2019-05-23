#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <memory>
#include <stack>

#include "State.hpp"

namespace Checkers {
    typedef State* StateRef;

    class StateMachine {
        public:
            StateMachine() { }
            void addState(StateRef newState, bool isReplacing = true);
            void removeState();
            void processStateChanges();
            StateRef& getActiveState();

        private:
            std::stack<StateRef> _states;
            StateRef _newState;
            bool _isRemoving;
            bool _isAdding, _isReplacing;
    };
}

#endif
