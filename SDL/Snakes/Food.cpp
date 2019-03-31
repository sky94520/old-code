#include "Food.h"
#include "TextureManager.h"
#include "Game.h"
Food::Food()
{
    m_bIsExisted = true;
}
bool Food::load(std::unique_ptr<LoaderParams> pParams)
{
    LoaderParams*p = pParams.get();
    m_x = p->getX();
    m_y = p->getY();
    m_width = p->getWidth();
    m_height = p->getHeight();
    m_textureID = p->getTextureID();
    //移除指针 或者
    pParams = NULL;
    //pParams.reset();
    return true;
}
void Food::update()
{
}
void Food::draw()
{
    float zoomTimes = TheGame::Instance()->getZoomTimes();
    SDL_Rect dest = {m_x,m_y,int(m_width * zoomTimes),int(m_height * zoomTimes)};
    TheTextureManager::Instance()->draw(m_textureID,NULL,&dest);
}
void Food::clean()
{
}
void Food::updatePosition()
{
}
