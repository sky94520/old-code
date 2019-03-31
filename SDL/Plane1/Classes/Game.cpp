#include "Game.h"
#include "TextureManager.h"
#include "InputHandle.h"
#include "GameObjectFactory.h"

#include "MenuButton.h"
#include "Player.h"
#include "Enemy.h"
#include "AnimatedGraphic.h"
#include "ScrollingBackground.h"

#include "MainMenuState.h"
#include "PlayState.h"

Game*Game::s_pInstance = NULL;

Game::Game()
{
    m_pGameStateMachine = NULL;

    m_bLevelComplete = false;
}
Game*Game::Instance()
{
	if (s_pInstance == NULL)
		s_pInstance = new Game();

	return s_pInstance;
}
bool Game::init(const char *title, int xpos, int ypos, int width, int height, int flags)
{
    m_bRunning = false;
	// init
	/*SDL_INIT_HAPIIC只有在有摇杆时有效，好像是这样*/
	if (SDL_Init(SDL_INIT_EVERYTHING^SDL_INIT_HAPTIC) >= 0)
	{
		/// if succeeded create our window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != NULL)
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		if (m_pRenderer != NULL)
		SDL_SetRenderDrawColor(m_pRenderer,210,250,255,255);
		else
		return false;
	}
	else
		return false;

	m_bRunning = true;
	//获取窗口大小
	SDL_GetWindowSize(m_pWindow,&m_gameWidth,&m_gameHeight);

	std::cout<<"Game\nwidth = "<<m_gameWidth<<std::endl;
	std::cout<<"height = "<<m_gameHeight<<std::endl;
	//add the code here..
	///保存tmx and so on
	m_levelFiles.push_back("assets/map1.tmx");
	///当前为关卡1
	m_currentLevel = 1;
    //人物生命
    /**这个我感觉有些纠结，因为在第二次或多次玩游戏时，
    并不会执行这条语句，所以我在PlayState里又加上了，好纠结
    */
    m_playerLives = 2;
	//加载render
	TheTextureManager::Instance()->bind(m_pRenderer);

    m_pGameStateMachine = new GameStateMachine();
    /**这个我同样纠结，因为这个类型同音乐类型
    差不多的，暂时一次性加载完成*/
    TheGameObjectFactory::Instance()->registerType("MenuButton",new MenuButtonCreator());
    TheGameObjectFactory::Instance()->registerType("Player",new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("Enemy",new EnmeyCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedGraphic",new AnimatedGraphicCreator());
    TheGameObjectFactory::Instance()->registerType("ScrollingBackground",new ScrollingBackgroundCreator());

    m_pGameStateMachine->pushState(new MainMenuState());
	return true;
}
void Game::render()
{
	///clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);
	///draw
	m_pGameStateMachine->render();
	///draw to the screen
	SDL_RenderPresent(m_pRenderer);
}
void Game::clean()
{
	delete m_pGameStateMachine;
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
void Game::handleEvents()
{
}
void Game::update()
{
    TheInputHandle::Instance()->update();
    m_pGameStateMachine->update();
}
void Game::quit()
{
    m_bRunning = false;
}
GameStateMachine* Game::getStateMachine()
{
    return m_pGameStateMachine;
}
