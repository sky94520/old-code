#pragma once
#include<iostream>
#include<vector>
#include<string>

#include "MainMenuState.h"
#include "TextureManager.h"
#include "InputHandle.h"
#include "MenuButton.h"

class GameObject;
class PauseState : public MenuState
{
 private:
    static void s_pauseToMain();
    static void s_resumePlay();

    static const std::string s_pauseID;

    std::vector<GameObject*> m_gameObjects;
 private:
    void setCallbacks(const std::vector<Callback>& callbacks);
 public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {return s_pauseID;}
};
