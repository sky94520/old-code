#ifndef _ObjectLayer_H__
#define __ObjectLayer_H__
#include<vector>

#include "Layer.h"
class GameObject;

class ObjectLayer : public Layer
{
    private:
    std::vector<GameObject*> m_gameObjects;
    public:
    virtual void update();
    virtual void render();
    std::vector<GameObject*>* getGameObjects()
    {
        return &m_gameObjects;
    }
};
#endif
