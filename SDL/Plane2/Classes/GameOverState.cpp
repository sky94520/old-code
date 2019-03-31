#include "GameOverState.h"

#include "PlayState.h"
#include "MainMenuState.h"
#include "TextureManager.h"
#include "StateParser.h"
#include "MenuButton.h"
#include "Game.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";
//init
bool GameOverState::onEnter()
{
    //parse the state
    StateParser stateParser;
    stateParser.parseState("assets/test.xml",s_gameOverID,
                           &m_gameObjects,&m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);

    setCallbacks(m_callbacks);

    std::cout<<"entering GameOver State\n";
    return true;
}
//exit
bool GameOverState::onExit()
{
    for(int i = 0;i < m_gameObjects.size();i++)
    {
        TheTextureManager::Instance()->
        clearFromTextureMap(m_textureIDList[i]);
    }
    std::cout<<"exiting GameOverState\n";
    return true;
}
void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
    //go through the game objects
    for(unsigned int i = 0;i < m_gameObjects.size();i++)
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
void GameOverState::update()
{
for(int i = 0;i < m_gameObjects.size();i++)
       m_gameObjects[i]->update();
}
void GameOverState::render()
{
for(int i = 0;i < m_gameObjects.size();i++)
       m_gameObjects[i]->draw();
}
GameOverState::GameOverState()
{
    //ctor
}

GameOverState::~GameOverState()
{
    //dtor
}
void GameOverState::s_gameOverToMain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}
void GameOverState::s_restartPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}
