#ifndef __Player_H__
#define __Player_H__

#include "ShooterObject.h"
#include "InputHandle.h"
#include "GameObjectFactory.h"

class Player:public ShooterObject
{
private:
    /*player can be invulnerable
    (受到伤害的 ) for a time*/
    int m_invulnerable;
    //复活后不受伤害的时间
    int m_invulnerableTime;
    int m_invulnerableCounter;
private:
    //bring the player back if there are lives left
    void ressurect();
    //handle any input from the keyboard,mouse,or joystick
    void handleInput();
    //handle any animation for the player
    void handleAnimation();
public:
    Player();
    ~Player();

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(std::unique_ptr<LoaderParams>const &pParams);
    virtual void collision();
};
class PlayerCreator : public BaseCreator
{
public:
    PlayerCreator() {}
    GameObject* createGameObject() const
    {
        return new Player();
    }
};
#endif
