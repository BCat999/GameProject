#include "CloseState.h"
#include "LockState.h"

void CloseState::unlock() {
    std::cout << "Unlock the Door, but it's not locked\n";
}

void CloseState::close() {
    std::cout << "Close the Door, but it's closing\n";
}
void CloseState::open() {
    std::cout << "Open the Door, it's open now\n";
    this->mContext->TransitionTo(new OpenState);
}
void CloseState::lock() {
    std::cout << "Lock the Door, it's lock now\n";
    this->mContext->TransitionTo(new LockState);
}