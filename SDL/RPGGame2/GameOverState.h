#ifndef __GameOverState_H__
#define __GameOverState_H__

#include<vector>
#include<iostream>

#include "MenuState.h"
#include "TextureManager.h"
#include "AnimatedGraphic.h"

class GameObject;

class GameOverState : public MenuState
{
    private:
        static void s_gameOverToMain();
        static void s_restartPlay();

        static const std::string s_gameOverID;

        std::vector<GameObject*> m_gameObjects;
    private:
        virtual void setCallbacks(const std::vector<Callback>& callbacks);
    public:
        GameOverState();
        virtual ~GameOverState();

        virtual void update();
        virtual void render();

        virtual bool onEnter();
        virtual bool onExit();

        virtual std::string getStateID() const {return s_gameOverID;}
};

#endif // GAMEOVERSTATE_H
