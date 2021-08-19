#include "LockState.h"

void LockState::unlock() {
	std::cout << "Unlock the Door, it's closed now\n";
	this->mContext->TransitionTo(new CloseState);
}

void LockState::close() {
	std::cout << "Close the Door, it's locked, of course it closed\n";
}

void LockState::open() {
	std::cout << "Open the Door, can't open \n";
}

void LockState::lock() {
	std::cout << "It's already locked\n";
}