#pragma once
#include<iostream>
class StateContext;

class State {
protected:
    StateContext* mContext;

public:
    virtual ~State() {
    }

    void set_context(StateContext* context);

    virtual void unlock() = 0;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void lock() = 0;
};