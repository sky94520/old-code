#include "Game.h"

#include "SDLGameObject.cpp"

#include "Player.hpp"
#include "Enemy.hpp"


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
	if (SDL_Init(
              SDL_INIT_EVERYTHING
              #ifndef __linux
              ^SDL_INIT_HAPTIC
              #endif
              ) >= 0)
	{
		// if succeeded create our window
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

	return true;
}
void Game::render()
{
	//clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);
	//draw
	for (std::vector<SDLGameObject*>::size_type i = 0; i < m_gameObjects.size();i++)
	{
		m_gameObjects[i]->draw();
	}
	//draw to the screen
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
/*	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			m_bRunning = false;
			break;
			default:
			break;
		}
	}*/
	TheInputHandle::Instance()->update();

}
void Game::update()
{
/**	for (auto vec : m_gameObjects)
	{
		vec->update();
	}*/
    for (std::vector<SDLGameObject*>::size_type i = 0; i < m_gameObjects.size();i++)
	{
		m_gameObjects[i]->update();
	}
}
void Game::quit()
{
    m_bRunning = false;
}
