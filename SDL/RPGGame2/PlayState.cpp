#include "PlayState.h"
#include "PauseState.h"
#include "Enemy.h"
#include "Game.h"
#include "GameOverState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
    TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }
/*    for(int i = 0;i < m_gameObjects.size();i++)
    {
        m_gameObjects[i]->update();
    }
    if(checkCollision(dynamic_cast<SDLGameObject*> (m_gameObjects[0]),dynamic_cast<SDLGameObject*> (m_gameObjects[1])))
    {
        TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
    }
*/
    pLevel->update();
}
void PlayState::render()
{
    pLevel->render();
/*    for(int i = 0;i < m_gameObjects.size();i++)
    {
        m_gameObjects[i]->draw();
    }
*/
}
//init
bool PlayState::onEnter()
{
	std::cout<<"entering PlayState"<<std::endl;
	//parse the state
/*	StateParser stateParser;
	stateParser.parseState("assets/test.xml",s_playID,
                        &m_gameObjects,&m_textureIDList);
	*/
    LevelParser levelParser;
    pLevel = levelParser.parseLevel("assets/map1.tmx");

//pLevel->output();

	return true;
}
bool PlayState::onExit()
{
	//TheErrorInfo::Instance()->log("exiting PlayState");
	std::cout<<"exiting PlayState"<<std::endl;

/*	for(int i = 0;i < m_gameObjects.size();i++)
	{
	    m_gameObjects[i]->clean();
	    delete m_gameObjects[i];
	}
	m_gameObjects.clear();*/
	for(int i = 0;i < m_textureIDList.size();i++)
	{
	    TheTextureManager::Instance()->
	    clearFromTextureMap(m_textureIDList[i]);
	}
	return true;
}
bool PlayState::checkCollision(SDLGameObject*p1,SDLGameObject*p2)
{
    int leftA,leftB;
    int rightA,rightB;
    int topA,topB;
    int bottomA,bottomB;

    leftA = p1->getPosition().getX();
    rightA = p1->getPosition().getX() + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = p1->getPosition().getY() + p1->getHeight();
    //calculate the sides of rect B
    leftB = p2->getPosition().getX();
    rightB = p2->getPosition().getX() + p2->getWidth();
    topB = p2->getPosition().getY();
    bottomB = p2->getPosition().getY() + p2->getHeight();
    //if any of sieds from A are outside of B
    if(bottomA <= topB){return false;}
    if(topA >= bottomB){return false;}
    if(rightA <= leftB){return false;}
    if(leftA >= rightB){return false;}

    return true;
}
