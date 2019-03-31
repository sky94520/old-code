#ifndef __LargeEnemy_H__
#define __LargeEnemy_H__
#include "Enemy.h"
class LargeEnemy : public Enemy
{
public:
    LargeEnemy():Enemy() {}
    //for polymorphism
    virtual ~Enemy() {}

    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    virtual void draw()
    {
    	Enemy::draw();
    }
    virtual void update()
    {
    	Enemy::update();
    }
    virtual void clean()
    {

    }
    virtual void collision()
    {

    }
    virtual std::string type()
    {
        return std::string("LargeEnemy");
    }
};
class LargeEnmeyCreator:public BaseCreator
{
public:
    GameObject* createGameObject() const
    {
        return new LargeEnemy();
    }
};
#endif
