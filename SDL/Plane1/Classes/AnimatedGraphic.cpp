#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic()
:ShooterObject()
{
    //ctor
    m_animSpeed = 1;
}
void AnimatedGraphic::load(std::unique_ptr<LoaderParams> const &pParams)
{
    ShooterObject::load(pParams);
    m_animSpeed = pParams->getAnimSpeed();
}
void AnimatedGraphic::update()
{
    m_currentFrame = int ((SDL_GetTicks()/(1000/m_animSpeed))%m_numFrames);
}
void AnimatedGraphic::draw()
{
	///change
    ShooterObject::draw();
}
void AnimatedGraphic::clean()
{
}
