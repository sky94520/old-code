#include "Fps.h"
#include "Game.h"

Fps::Fps(int frame) : m_nFrame(frame)
{
    m_nCurFrame = 0;
    m_nLastFrame = 60;
    m_tShowFPS = NULL;

    m_fpsTimer.start();
}
void Fps::update()
{
    if(m_capTimer.is_started() && m_capTimer.get_ticks() < 1000/m_nFrame)
    {
        SDL_Delay(int(1000.f/m_nFrame - m_capTimer.get_ticks()));
    }
    else
        m_capTimer.start();
    //达到一秒
    if(m_fpsTimer.get_ticks() >= 1000)
    {
        m_fpsTimer.start();
        m_nLastFrame = m_nCurFrame;
        m_nCurFrame = 0;
        SDL_DestroyTexture(m_tShowFPS);
        m_tShowFPS = NULL;
    }
    else
        m_nCurFrame++;
}
void Fps::draw(SDL_Renderer*ren)
{

    if (m_tShowFPS == NULL)
    {
        std::stringstream str;
        str<<"FPS:"<<m_nLastFrame;
        m_tShowFPS = TheGame::Instance()->RenderText(ren,str.str(),"assets/lazy.ttf", {255,0,0},50);
    }
    SDL_Rect srcRect = {0,0,0,0};
    SDL_Rect destRect = {0,0,0,0};
    SDL_QueryTexture(m_tShowFPS,NULL,NULL,&srcRect.w,&srcRect.h);
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
    SDL_RenderCopy(ren,m_tShowFPS,&srcRect,&destRect);
}
