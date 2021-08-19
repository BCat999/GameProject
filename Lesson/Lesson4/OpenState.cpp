#include "OpenState.h"

void OpenState::unlock() {
	std::cout << "The door not locked\n";
}

void OpenState::close() {
	std::cout << "Close the Door, it's closenow\n";
	this->mContext->TransitionTo(new CloseState);
}

void OpenState::open() {
	std::cout << "Open the Door, it's already open\n";
}

void OpenState::lock() {
	std::cout << "Can't lock the Door, please close the Door first!\n";
}