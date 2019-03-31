#include "PlayState.h"
#include "PauseState.h"
#include "Enemy.h"
#include "Game.h"
#include "GameOverState.h"
#include "SoundManager.h"
#include "BulletHandle.h"

const std::string PlayState::s_playID = "PLAY";
//init
bool PlayState::onEnter()
{
	std::cout<<"entering PlayState"<<std::endl;
	//parse the state
/*	StateParser stateParser;
	stateParser.parseState("assets/test.xml",s_playID,
                        &m_gameObjects,&m_textureIDList);
	*/
	//load tmx
    LevelParser levelParser;
    pLevel = levelParser.parseLevel("assets/map1.tmx");
    //load music
    try
    {
    	TheTextureManager::Instance()->load("assets/bullet1.png","bullet1");
    	TheTextureManager::Instance()->load("assets/lives.png","lives");
    	TheSoundManager::Instance()->load("assets/DST_ElectroRock.wav","bg1",SOUND_MUSIC);
    	TheSoundManager::Instance()->load("assets/boom.wav","boom",SOUND_SFX);
    }
    catch(const std::runtime_error &e)
    {
    	std::cout<<e.what()<<std::endl;
    }
    TheSoundManager::Instance()->playMusic("bg1",-1);
//pLevel->output();

	return true;
}
void PlayState::update()
{
    if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
    TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }
    TheBulletHandle::Instance()->update();
    pLevel->update();
}
void PlayState::render()
{
    pLevel->render();
    TheBulletHandle::Instance()->draw();
    //显示人物生命
    for(int i = 0;i < TheGame::Instance()->getPlayerLives();i++)
    {
    	TheTextureManager::Instance()->draw("lives",i * 32,0,32,30);
    }
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
bool PlayState::checkCollision(ShooterObject*p1,ShooterObject*p2)
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
