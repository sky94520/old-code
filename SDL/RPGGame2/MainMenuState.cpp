#include "MainMenuState.h"

#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"

const std::string MainMenuState::s_menuID = "MENU";

bool MainMenuState::onEnter()
{
    //parse the state
    StateParser stateParser;
    stateParser.parseState("assets/test.xml",s_menuID,&m_gameObjects,&m_textureIDList);

    m_callbacks.push_back(0);//push 0 callbackID start from 1
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);
    //set the callbacks for menu items
    setCallbacks(m_callbacks);
    std::cout<<"entering MenuState\n";

    return true;
}
bool MainMenuState::onExit()
{
    for(int i = 0;i < m_textureIDList.size();i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    std::cout<<"exiting MenuState\n";
    return true;
}
void MainMenuState::update()
{
    for(int i = 0;i < m_gameObjects.size();i++)
    {
        m_gameObjects[i]->update();
    }
}
void MainMenuState::render()
{
    for(int i = 0;i < m_gameObjects.size();i++)
    {
        m_gameObjects[i]->draw();
    }
}
void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
    //go through the game objects
    for(int i = 0;i < m_gameObjects.size();i++)
    {
        //if they are of type MenuButton then assign a callback
        //based on the id passed in from the file
        if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}
void MainMenuState::s_menuToPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}
void MainMenuState::s_exitFromMenu()
{
    TheGame::Instance()->quit();
}
