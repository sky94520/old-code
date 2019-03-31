#ifndef __MainMenuState_H__
#define __MainMenuState_H__

#include<iostream>
#include<stdexcept>

#include "MenuState.h"
#include "GameObject.h"

class MainMenuState : public MenuState
{
private:
    //call back functions for menu items
    static void s_menuToPlay();
    static void s_exitFromMenu();

    static const std::string s_menuID;

    std::vector<GameObject*> m_gameObjects;
private:
    virtual void setCallbacks(const std::vector<Callback>& callbacks);
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const
    {
        return s_menuID;
    }

};
#endif
