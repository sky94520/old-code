#include "PlayState.h"
#include "TextureManager.h"
#include "Food.h"
#include "Snake.h"

std::string PlayState::s_playID = "PLAY";
/*初始化*/
PlayState::PlayState()
{
}
bool PlayState::onEnter()
{
    /*加载图片资源*/
    try
    {
        TheTextureManager::Instance()->load("assets/apple.png","apple");
        m_textureIDList.push_back("apple");
        TheTextureManager::Instance()->load("assets/snake.png","snake");
        m_textureIDList.push_back("snake");

    }
    catch (std::runtime_error &e)
    {
    }
    /*加载声音资源*/
    /*初始化对象*/
    Food*food = new Food();
    food->load(std::unique_ptr<LoaderParams> (new LoaderParams(0,0,50,50,"apple")));
    m_gameObjects.push_back(food);
    //初始化蛇
    Snake*snake = new Snake();
    snake->load(std::unique_ptr<LoaderParams> (new LoaderParams(400,400,50,50,"snake")));
    m_gameObjects.push_back(snake);
    return true;
}
bool PlayState::onExit()
{
    /*释放图片资源*/
    for (int i = 0;i < m_textureIDList.size();i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    //释放对象
    return true;
}
void PlayState::render()
{
    for (int i = 0;i < m_gameObjects.size();i++)
    {
        m_gameObjects[i]->draw();
    }

}
void PlayState::update()
{
    for (int i = 0;i < m_gameObjects.size();i++)
    {
        m_gameObjects[i]->update();
    }
}
