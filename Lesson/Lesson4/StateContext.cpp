#include "StateContext.h"

StateContext::StateContext(State* state) : mState(nullptr) {
    this->TransitionTo(state);
}
StateContext::~StateContext() {
    delete mState;
}
void StateContext::TransitionTo(State* state) {
    std::cout << "Transition to " << typeid(*state).name() << ".\n";
    if (this->mState != nullptr)
        delete this->mState;
    this->mState = state;
    this->mState->set_context(this);
}
void StateContext::unlockDoor() {
    this->mState->unlock();
}
void StateContext::openDoor() {
    this->mState->open();
}
void StateContext::closeDoor() {
    this->mState->close();
}
void StateContext::lockDoor() {
    this->mState->lock();
}