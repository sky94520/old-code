#include<vector>
#include<fstream>

#include "SDLGameObject.h"
#include "GameStateMachine.h"
//#include "Player.hpp"
//#include "Enemy.hpp"

#pragma once
class Game
{
  private:
     Game();
     //SDL窗口
     SDL_Window*m_pWindow;
     SDL_Renderer*m_pRenderer;
     //渲染器
     bool m_bRunning;
     //游戏类
     std::vector<SDLGameObject*>m_gameObjects;

	static Game*s_pInstance;
	//FSM
	GameStateMachine*m_pGameStateMachine;
  public:
     static Game*Instance();

     void init(const char *title, int xpos, int ypos, int height, int width, int flags);
     void render();
	 void update();
	 void handleEvents();
	 void clean();

    SDL_Renderer* getRenderer() const {return m_pRenderer;}
    bool running(){return m_bRunning;}
    void quit();
};
typedef Game TheGame;
Game*Game::s_pInstance = NULL;