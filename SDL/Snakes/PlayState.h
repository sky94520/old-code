#ifndef __PlayState_H__
#define __PlayState_H__

#include<vector>
#include "GameObject.h"
#include "GameState.h"
#include "Vector2D.h"

class PlayState : public GameState
{
 private:
    static std::string s_playID;
    std::vector<std::string> m_textureIDList;
    std::vector<GameObject*> m_gameObjects;
 public:
     PlayState();
    virtual bool onEnter();
    virtual bool onExit();
    virtual void update();
    virtual void render();

    std::string getStateID() const
    {
        return s_playID;
    }
};
#endif
