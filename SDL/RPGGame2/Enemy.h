#pragma once
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject
{
  public:
    Enemy();
    ~Enemy();

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams*pParams);
};
class EnmeyCreator:public BaseCreator
{
 public:
    GameObject* createGameObject() const
    {
        return new Enemy();
    }
};
