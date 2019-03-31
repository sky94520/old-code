#ifndef __Enemy_H__
#define __Enemy_H__

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Enemy : public ShooterObject
{
protected:
    int m_health;
public:
	Enemy():ShooterObject() {}
    //for polymorphism
    virtual ~Enemy() {}

    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

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
