#ifndef _ObjectLayer_H__
#define __ObjectLayer_H__

#include<vector>

#include "Layer.h"
#include "CollisionManager.h"

class GameObject;

class ObjectLayer : public Layer
{
private:
    std::vector<GameObject*> m_gameObjects;
    CollisionManager m_collisionManager;
public:
    virtual void update(Level*pLevel);
    virtual void render();
    std::vector<GameObject*>* getGameObjects()
    {
        return &m_gameObjects;
    }
};
#endif
