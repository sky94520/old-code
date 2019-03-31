#ifndef __AnimatedGraphic_H__
#define __AnimatedGraphic_H__

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public ShooterObject
{
    private:
        int m_animSpeed;
    public:
        AnimatedGraphic();

        virtual void draw();
        virtual void clean();
        virtual void update();
        virtual void load(std::unique_ptr<LoaderParams>const &pParams);
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
