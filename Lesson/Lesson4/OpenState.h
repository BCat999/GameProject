#pragma once
#pragma once
#include "State.h"
#include "StateContext.h"
#include "CloseState.h"

class OpenState : public State {
public:
    void unlock() override;
    void close() override;
    void open() override;
    void lock() override;
};
