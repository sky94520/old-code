#include "ShooterObject.h"
#include "Game.h"


void ShooterObject::load(std::unique_ptr<LoaderParams> const &p)
{
	LoaderParams*pParams = p.get();

    m_position = Vector2D(pParams->getX(),pParams->getY());
    m_velocity = Vector2D(0,0);
    m_acceleration = Vector2D(0,0);

    m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();

	m_currentRow = 1;
	m_moveSpeed = 0;

	m_numFrames = pParams->getNumFrames();
}
void ShooterObject::draw()
{
	TheTextureManager::Instance()->drawFrame(m_textureID,(int)m_position.getX(),(int)m_position.getY(),m_width,m_height,m_currentRow,m_currentFrame,m_angle,m_alpha);
}
void ShooterObject::clean()
{
}
void ShooterObject::update()
{
	m_currentFrame = (SDL_GetTicks()/100)%6;

	m_velocity += m_acceleration;
	m_position += m_velocity;
}
void ShooterObject::doDyingAnimation()
{
	//keep scrolling with the map
	scroll(TheGame::Instance()->getScrollSpeed());
	m_currentFrame = int(((SDL_GetTicks()/(1000/3)) % m_numFrames));
	if(m_dyingCounter == m_dyingTime)
	{
		m_bDead = true;
	}
	//simple counter,fine with fixed frame rate
	m_dyingCounter++;
}
