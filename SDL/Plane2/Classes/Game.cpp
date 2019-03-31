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

Game*Game::s_pInstance = NULL;

Game::Game()
{
    m_pGameStateMachine = NULL;
    //人物生命
    m_playerLives = 4;
    //当前关卡级别
    m_currentLevel = 1;
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
	/*SDL_INIT_HAPIIC只有在安卓内有效*/
	if (SDL_Init(
              SDL_INIT_EVERYTHING
              #ifndef __linux
              ^SDL_INIT_HAPTIC
              #endif
              ) >= 0)
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
	//加载render
	TheTextureManager::Instance()->bind(m_pRenderer);

    m_pGameStateMachine = new GameStateMachine();
 //   m_pGameStateMachine->changeState(new MenuState());
    TheGameObjectFactory::Instance()->registerType("MenuButton",
                                                   new MenuButtonCreator());
    TheGameObjectFactory::Instance()->registerType("Player",new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("Enemy",new EnmeyCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedGraphic",new AnimatedGraphicCreator());
    TheGameObjectFactory::Instance()->registerType("ScrollingBackground",new ScrollingBackgroundCreator());

    m_pGameStateMachine->changeState(new MainMenuState());
	return true;
}
void Game::render()
{
	///clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);
	///draw
	//TheTextureManager::Instance()->draw("animate",100,100,128,128);
	m_pGameStateMachine->render();
	///draw to the screen
	SDL_RenderPresent(m_pRenderer);
}
void Game::clean()
{
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
