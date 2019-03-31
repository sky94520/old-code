#ifndef __Enemy_H__
#define __Enemy_H__

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Enemy : public ShooterObject
{
protected:
    int m_health;
private:
    void doDyingAnimation();
public:
    Enemy():ShooterObject()
    {
        /**就目前来说，LoaderParams并没有生命值，
        所以先默认设置*/
        m_dyingTime = 50;
        m_health = 3;
        m_moveSpeed = 3;
        m_bulletFiringSpeed = 50;
    }
    //for polymorphism
    virtual ~Enemy()
    {
        // std::cout<<"enemy is released.\n";
    }

    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void collision();

    virtual std::string type()
    {
        return std::string("Enemy");
    }
};
class EnmeyCreator:public BaseCreator
{
public:
    GameObject* createGameObject() const
    {
        return new Enemy();
    }
};
#endif
