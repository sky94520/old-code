#ifndef __AnimatedGraphic_H__
#define __AnimatedGraphic_H__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
    private:
        int m_animSpeed;
    public:
        AnimatedGraphic();

        virtual void draw();
        virtual void clean();
        virtual void update();
        virtual void load(const LoaderParams*pParams);
};
class AnimatedGraphicCreator:public BaseCreator
{
 public:
    virtual GameObject* createGameObject() const
    {
        return new AnimatedGraphic();
    }
};
#endif // AnimatedGraphic_H
