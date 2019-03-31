#ifndef __ShooterObject_H__
#define __ShooterObject_H__

#include "GameObject.h"
#include "TextureManager.h"
#include "Vector2D.h"

class Game;

class ShooterObject:public GameObject
{
protected:
    int m_bulletFiringSpeed;
    int m_bulletCounter;
    //how fast will this object move
    int m_moveSpeed;
    //how long will the death animation takes?with a counter
    int m_dyingTime;
    int m_dyingCounter;
    //has the explosion sound played?
    bool m_bPlayerDeathSound;
protected:
    //draw the animation for the object being destroyed
    void doDyingAnimation();
public:
    ShooterObject() : GameObject(),m_bulletFiringSpeed(0),
    m_bulletCounter(0),m_moveSpeed(0),
    m_dyingTime(0),m_dyingCounter(0),m_bPlayerDeathSound(true)
    {}
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    virtual void collision() {} //not implemented in this class
    virtual std::string type()
    {
        return std::string("ShooterObject");
    }
    //for polymorphism
    virtual ~ShooterObject() {}
    Vector2D& getPosition()
    {
        return m_position;
    }
    int getWidth()
    {
        return m_width;
    }
    int getHeight()
    {
        return m_height;
    }
};
#endif
