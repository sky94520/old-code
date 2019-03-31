#pragma once
#include<iostream>
#include "MenuState.h"
#include "StateParser.h"

class GameObject;

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

    virtual std::string getStateID() const {return s_menuID;}

};
