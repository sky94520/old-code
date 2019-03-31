#include "Game.h"

#include "SDLGameObject.cpp"

#include "Player.hpp"
#include "Enemy.hpp"

#include "PlayState.hpp"
#include "MenuState.hpp"

#include "GameStateMachine.cpp"

Game*Game::s_pInstance = NULL;

Game::Game()
{
}
Game*Game::Instance()
{
	if (s_pInstance == NULL)
		s_pInstance = new Game();

	return s_pInstance;
}
bool Game::init(const char *title, int xpos, int ypos, int height, int width, int flags)
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
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
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
	//加载图片资源 单例类
	if (TextureManager::Instance()->load("animate-alpha.png","animate",m_pRenderer) == false )
	return false;

//	m_gameObjects.push_back(new SDLGameObject(new LoaderParams(50,300,128,82,"animate")));
	m_gameObjects.push_back(new Player(new LoaderParams(0,100,128,82,"animate")));
	m_gameObjects.push_back(new Enemy(new LoaderParams(0,200,128,82,"animate")));
	//新增
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MenuState());
	return true;
}
void Game::render()
{
	///clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);
	///draw
	for (std::vector<SDLGameObject*>::size_type i = 0; i < m_gameObjects.size();i++)
	{
		m_gameObjects[i]->draw();
	}
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
	TheInputHandle::Instance()->update();

	if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
	    m_pGameStateMachine->changeState(new PlayState());
	}
}
void Game::update()
{
    for (std::vector<SDLGameObject*>::size_type i = 0; i < m_gameObjects.size();i++)
	{
		m_gameObjects[i]->update();
	}
	m_pGameStateMachine->update();
}
void Game::quit()
{
    m_bRunning = false;
}
