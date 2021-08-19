#pragma once
#include "State.h"
#include "StateContext.h"
#include "OpenState.h"
class CloseState : public State {
public:
    void unlock() override;
    void close() override;
    void open() override;
    void lock() override;
};