#include "Game.h"

#include "SDLGameObject.cpp"

#include "Player.hpp"
#include "Enemy.hpp"

#include "PlayState.hpp"
#include "MenuState.hpp"

#include "GameStateMachine.cpp"

#include "MenuButton.hpp"

void Game::init(const char *title, int xpos, int ypos, int height, int width, int flags)
{
	m_bRunning = false;
	// init
	/* SDL_INIT_HAPIICֻ */
	if (SDL_Init(SDL_INIT_EVERYTHING
#ifndef __linux
				 ^ SDL_INIT_HAPTIC
#endif
		) >= 0)
	{
		if ((m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags)) != NULL)
		{
			if ((m_pRenderer =
				 SDL_CreateRenderer(m_pWindow, -1,
									SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED)) != NULL)
			{
				SDL_SetRenderDrawColor(m_pRenderer, 210, 250, 255, 255);
			}
			else
				throw String(SDL_GetError());
		}
		else
			throw String(SDL_GetError());
	}
	else
	{
		throw String(SDL_GetError());
	}

	// load
	if (!TextureManager::Instance()->load("animate-alpha.png", "animate", m_pRenderer))
		throw String(SDL_GetError());
    if (!TextureManager::Instance()->load("button.png", "button", m_pRenderer))
        throw String(SDL_GetError());
	// add codes here...
	m_gameObjects.push_back(new Player(new LoaderParams(0, 100, 128, 82, "animate")));
	//m_gameObjects.push_back(new Enemy(new LoaderParams(0, 200, 128, 82, "animate")));
	m_gameObjects.push_back(new MenuButton(new LoaderParams(300,300,400,100,"button")));

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MenuState());

	m_bRunning = true;
}
/*渲染*/
void Game::render()
{
	// /clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);
	// /draw
	for (std::vector < SDLGameObject * >::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
	m_pGameStateMachine->render();
	// /draw to the screen
	SDL_RenderPresent(m_pRenderer);
}
/*处理按键*/
void Game::handleEvents()
{
	TheInputHandle::Instance()->update();

	if (TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(new PlayState());
	}
}
/*更新*/
void Game::update()
{
	for (std::vector < SDLGameObject * >::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
	m_pGameStateMachine->update();
}
void Game::quit()
{
	m_bRunning = false;
}
Game::Game()
{
}
Game *Game::Instance()
{
	if (s_pInstance == NULL)
		s_pInstance = new Game();

	return s_pInstance;
}
void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
