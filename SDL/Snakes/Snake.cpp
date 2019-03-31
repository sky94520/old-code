#include "Snake.h"
#include "TextureManager.h"
#include "InputHandle.h"
#include "Game.h"

Snake::Snake()
{
    m_headDirection = HEAD_RIGHT;
}
Snake::~Snake()
{
}
bool Snake::load(std::unique_ptr<LoaderParams> pParams)
{
    LoaderParams*p = pParams.get();
    m_x = p->getX();
    m_y = p->getY();
    m_width = p->getWidth();
    m_height = p->getHeight();
    m_textureID = p->getTextureID();

    pParams.reset();
    //获取分辨率
    int w = TheGame::Instance()->getGameWidth();
    int h = TheGame::Instance()->getGameHeight();

    for (int i = 0; i < 4; i++)
    {
        m_node.push_back(SnakeNode {int(w/2 + m_width * (1 - i)),h/2});
    }
    return true;
}
void Snake::draw()
{
    SDL_Rect clip = {0,0,m_width,m_height};
    SDL_Rect dest = {0,0,m_width ,m_height};
    double angle = 0;

    for (int i = 0; i < m_node.size(); i ++)
    {
        /*蛇头,由m_headDirection修改角度*/
        if (0 == i)
        {
            clip.x = clip.w * 2;
            /*enum常量即为数字
            java就不能这样使用*/
            angle = m_headDirection * 90;
            dest.x = m_node[i].x;
            dest.y = m_node[i].y;
            TheTextureManager::Instance()->draw(m_textureID,&clip,&dest,angle);
        }
        else if (i == m_node.size() -1)
        {
            clip.x = 0;
            dest.x = m_node[i].x;
            dest.y = m_node[i].y;
            //angle
            int mRelativePosX = m_node[i - 1].x - m_node[i].x;
            int mRelativePosY = m_node[i - 1].y - m_node[i].y;
            //right
            if(mRelativePosX > 0)
                angle = 0;
            //down
            else if(mRelativePosY > 0)
                angle = 90;
            //left
            else if(mRelativePosX < 0)
                angle = 180;
            //up
            else if(mRelativePosY < 0)
                angle = 270;
            TheTextureManager::Instance()->draw(m_textureID,&clip,&dest,angle);
        }
        else
        {
            clip.x = clip.w;
            angle = 0;
            dest.x = m_node[i].x;
            dest.y = m_node[i].y;

            TheTextureManager::Instance()->draw(m_textureID,&clip,&dest,angle);
        }
    }
}
void Snake::update()
{
    handleInput();
    if (!m_timer.is_started())
        m_timer.start();
    if (/*handleInput() || */m_timer.get_ticks() >= 400)
    {
        /*除蛇头外都进"一"*/
        for(int i = m_node.size() - 1; i > 0; i--)
        {
            m_node[i].x = m_node[i - 1].x;
            m_node[i].y = m_node[i - 1].y;
        }
        /*蛇头坐标增加*/
        switch (m_headDirection)
        {
        case HEAD_UP:
            m_node[0].y -= m_height;
            break;
        case HEAD_DOWN:
            m_node[0].y += m_height;
            break;
        case HEAD_LEFT:
            m_node[0].x -= m_width;
            break;
        case HEAD_RIGHT:
            m_node[0].x += m_width;
            break;
        default :
            break;
        }
        m_timer.start();
    }
}
void Snake::clean()
{
}
bool Snake::handleInput()
{
    if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_UP) && m_headDirection != HEAD_DOWN)
    {
        m_headDirection = HEAD_UP;
    }
    else if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_DOWN) && m_headDirection != HEAD_UP)
        m_headDirection = HEAD_DOWN;
    else if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && m_headDirection != HEAD_RIGHT)
        m_headDirection = HEAD_LEFT;
    else if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && m_headDirection != HEAD_LEFT)
        m_headDirection = HEAD_RIGHT;
}
