#include "PlayState.h"
#include "PauseState.h"
#include "Enemy.h"
#include "Game.h"
#include "GameOverState.h"
#include "SoundManager.h"
#include "BulletHandle.h"
/**这里我还是纠结，m_textureIDList应该放到一个xml文件，
然后全部加载，这样，说实话，要改变LevelParser的实现，
如果不改变。加载界面怎么办，现在可以明显看出，在转换界面
会发生明显的卡顿，这在以后肯定不行的，这可是电脑啊，要是放在
手机上怎么办啊！！！正在向两全其美的解决办法*/
const std::string PlayState::s_playID = "PLAY";
//init
bool PlayState::onEnter()
{
    std::cout<<"entering PlayState"<<std::endl;
    ///load tmx
    LevelParser levelParser;
    try
    {
    	int nCurrentLevel = TheGame::Instance()->getCurrentLevel();
    	std::string file = TheGame::Instance()->getLevelFiles()[nCurrentLevel - 1];
        pLevel = levelParser.parseLevel(file.c_str());
    }
    catch(std::runtime_error &e)
    {
        std::cerr<<e.what()<<std::endl;
        return false;
    }
    //设置人物生命
    TheGame::Instance()->setPlayerLives(2);
    ///load sources
    try
    {
        TheTextureManager::Instance()->load("assets/bullet1.png","bullet1");
        TheTextureManager::Instance()->load("assets/lives.png","lives");
        TheTextureManager::Instance()->load("assets/largeexplosion.png","largeexplosion");
        TheTextureManager::Instance()->load("assets/smallexplosion.png","smallexplosion");
        TheSoundManager::Instance()->load("assets/phaser.wav","phaser",SOUND_SFX);
        TheSoundManager::Instance()->load("assets/DST_ElectroRock.ogg","bg1",SOUND_MUSIC);
        TheSoundManager::Instance()->load("assets/boom.wav","explode",SOUND_SFX);
    }
    catch(const std::runtime_error &e)
    {
        std::cerr<<e.what()<<std::endl;
    }
    TheSoundManager::Instance()->playMusic("bg1",-1);

    return true;
}
void PlayState::update()
{
    if(pLevel != NULL)
        pLevel->update();
    TheBulletHandle::Instance()->update();

    if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }
    if(TheGame::Instance()->getPlayerLives() <= 0)
    {
        TheGame::Instance()->getStateMachine() ->changeState(new GameOverState());
    }
}
void PlayState::render()
{
    pLevel->render();
    TheBulletHandle::Instance()->draw();
    //ÏÔÊ¾ÈËÎïÉúÃü
    for(int i = 0; i < TheGame::Instance()->getPlayerLives(); i++)
    {
        TheTextureManager::Instance()->draw("lives",i * 32,0,32,30);
    }
}
bool PlayState::onExit()
{
    std::cout<<"exiting PlayState"<<std::endl;
    for(std::vector<std::string>::size_type i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->
        clearFromTextureMap(m_textureIDList[i]);
    }
    TheInputHandle::Instance()->reset();
    TheBulletHandle::Instance()->clearBullets();
    this->~PlayState();
    return true;
}
