#include <iostream>
#include "State.h"
#include "StateContext.h"
#include "OpenState.h"
#include "LockState.h"

void OpenDoorState() {
    StateContext* context = new StateContext(new OpenState);
    context->unlockDoor();
    context->openDoor();
    context->closeDoor();
    context->lockDoor();
    delete context;
}
void CloseDoorState() {
    StateContext* context = new StateContext(new CloseState);
    context->unlockDoor();
    context->openDoor();
    context->closeDoor();
    context->lockDoor();
    delete context;
}
void LockDoorState() {
    StateContext* context = new StateContext(new LockState);
    context->unlockDoor();
    context->openDoor();
    context->closeDoor();
    context->lockDoor();
    delete context;
}
int main() {
    std::cout << "\nTry an OpenDoor:\n\n";
    OpenDoorState();
    std::cout << "\nTry an CloseDoor:\n\n";
    CloseDoorState();
    std::cout << "\nTry an LockDoor:\n\n";
    LockDoorState();
    return 0;
}