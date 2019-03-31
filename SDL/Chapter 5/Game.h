#include<vector>

#include "SDLGameObject.h"
#include "GameStateMachine.h"
//#include "Player.hpp"
//#include "Enemy.hpp"

#pragma once
class Game
{
  private:
     Game();
     //SDL的窗口及渲染器
     SDL_Window*m_pWindow;
     SDL_Renderer*m_pRenderer;
     //是否退出游戏循环
     bool m_bRunning;
     //人物类
     std::vector<SDLGameObject*>m_gameObjects;

	static Game*s_pInstance;

	GameStateMachine*m_pGameStateMachine;
  public:
     static Game*Instance();

     bool init(const char *title, int xpos, int ypos, int height, int width, int flags);
     void render();
	 void update();
	 void handleEvents();
	 void clean();

    SDL_Renderer* getRenderer() const {return m_pRenderer;}
    bool running(){return m_bRunning;}
    void quit();
};
