#ifndef __ScrollingBackground_H__
#define __ScrollingBackground_H__

#include "SDL2/SDL.h"
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class ScrollingBackground : public ShooterObject
{
private:
    int m_scrollSpeed;

    SDL_Rect m_srcRect1;
    SDL_Rect m_srcRect2;

    SDL_Rect m_destRect1;
    SDL_Rect m_destRect2;
public:
    ScrollingBackground():ShooterObject(){}
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    virtual void update();
    virtual void draw();
    virtual void clean();
};
class ScrollingBackgroundCreator : public BaseCreator
{
	public:
    virtual GameObject*createGameObject() const
    {
    	return new ScrollingBackground();
    }
};
#endif
