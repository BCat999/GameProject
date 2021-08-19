#pragma once
#include "State.h"
#include <typeinfo>

class StateContext {
private:
    State* mState;
public:
    StateContext(State* state);
    ~StateContext();
    void TransitionTo(State* state);
    void unlockDoor();
    void openDoor();
    void closeDoor();
    void lockDoor();
};