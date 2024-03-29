#include "ScrollingBackground.h"
#include "TextureManager.h"
#include "Game.h"

void ScrollingBackground::load(std::unique_ptr<LoaderParams> const &pParams)
{
	ShooterObject::load(std::move(pParams));

	m_scrollSpeed = pParams->getAnimSpeed();

	m_scrollSpeed = 1;

	m_srcRect1.x = 0;
	m_srcRect1.y = 0;
	m_destRect1.x = m_position.getX();
	m_destRect1.y = m_position.getY();

	m_srcRect1.w = m_destRect1.w = m_width;
	m_srcRect1.h = m_destRect1.h = m_height;

	m_srcRect2.x = 0;
	m_srcRect2.y = 0;
	m_destRect2.x = m_position.getX() + m_width;
	m_destRect2.y = m_position.getY();

	m_srcRect2.w = m_destRect2.w = m_width;
	m_srcRect2.h = m_destRect2.h = m_height;


}
void ScrollingBackground::update()
{
	if(m_destRect1.x + m_destRect1.w <= 0)
	{
		m_destRect1.x = m_width;
	}
	else if(m_destRect2.x + m_destRect2.w <= 0)
	{
		m_destRect2.x = m_width;
	}
	else
	{
		m_destRect1.x -= m_scrollSpeed;
		m_destRect2.x -= m_scrollSpeed;
	}
}
void ScrollingBackground::draw()
{
	//draw first rect
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(),
						TheTextureManager::Instance()->getTextureMap()[m_textureID],
						&m_srcRect1,&m_destRect1,0,0,SDL_FLIP_NONE);
    //draw second rect
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(),
						TheTextureManager::Instance()->getTextureMap()[m_textureID],
						&m_srcRect2,&m_destRect2,0,0,SDL_FLIP_NONE);

}
void ScrollingBackground::clean()
{
}
