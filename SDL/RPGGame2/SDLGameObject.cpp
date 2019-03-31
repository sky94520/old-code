#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject()
:GameObject()
{
}
SDLGameObject::~SDLGameObject()
{
}
void SDLGameObject::load(const LoaderParams*pParams)
{
    m_position = Vector2D(pParams->getX(),pParams->getY());
    m_velocity = Vector2D(0,0);
    m_acceleration = Vector2D(0,0);

    m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();

	m_currentRow = 1;
	m_currentFrame = 1;

	m_numFrames = pParams->getNumFrames();
}
void SDLGameObject::draw()
{
    if(m_velocity.getX() > 0)
    {
      	TheTextureManager::Instance()->drawFrame(m_textureID,(int)m_position.getX(),(int)m_position.getY(),m_width,m_height,m_currentRow,m_currentFrame,SDL_FLIP_HORIZONTAL);
    }
    else
	    TheTextureManager::Instance()->drawFrame(m_textureID,(int)m_position.getX(),(int)m_position.getY(),m_width,m_height,m_currentRow,m_currentFrame);
}
void SDLGameObject::clean()
{
}
void SDLGameObject::update()
{
	m_currentFrame = (SDL_GetTicks()/100)%6;

	m_velocity += m_acceleration;
	m_position += m_velocity;
}
