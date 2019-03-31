#ifndef __MenuState_H__
#define __MenuState_H__

#include <vector>

#include "GameState.h"

class MenuState:public GameState
{
protected:
    typedef void(*Callback)();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

    std::vector<Callback> m_callbacks;

public:
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};
#endif
