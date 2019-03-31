#include "PauseState.h"

#include "Game.h"

const std::string PauseState::s_pauseID = "PAUSE";
//init
bool PauseState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("assets/test.xml",
                           s_pauseID,&m_gameObjects,&m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_resumePlay);
    m_callbacks.push_back(s_pauseToMain);

    setCallbacks(m_callbacks);
    std::cout<<"entering PauseState"<<std::endl;
    return true;
}
//exit
bool PauseState::onExit()
{
    for(int i = 0;i < m_gameObjects.size();i++)
    {
        TheTextureManager::Instance()->
        clearFromTextureMap(m_textureIDList[i]);
    }
    std::cout<<"exiting PauseState\n";
    return true;
}
void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
{
    //go through tje game objects
    for(int i = 0;i < m_gameObjects.size();i++)
    {
        //if they are of type MenuButton then assign a callback
        //based on the id passed in from the file
        if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
        {
            MenuButton*pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(m_callbacks[pButton->getCallbackID()]);
        }
    }
}
void PauseState::update()
{
    for(int i = 0;i < m_gameObjects.size();i++)
    {
        m_gameObjects[i]->update();
    }
}
void PauseState::render()
{
    for(int i = 0;i < m_gameObjects.size();i++)
    {
        m_gameObjects[i]->draw();
    }
}
void PauseState::s_pauseToMain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}
void PauseState::s_resumePlay()
{
    TheGame::Instance()->getStateMachine()->popState();
}
