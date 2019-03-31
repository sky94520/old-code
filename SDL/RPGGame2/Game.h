#ifndef __Game_H__
#define __Game_H__

#include<vector>
#include<iostream>

#include "SDL2/SDL.h"

#include "TextureManager.h"
#include "InputHandle.h"
#include "GameStateMachine.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "Player.h"

#include "MainMenuState.h"
#include "Enemy.h"
#include "AnimatedGraphic.h"

class Game
{
  private:
     Game();
     //SDL的窗口及渲染器
     SDL_Window*m_pWindow;
     SDL_Renderer*m_pRenderer;
     //是否退出游戏循环
     bool m_bRunning;

	 static Game*s_pInstance;

	 GameStateMachine*m_pGameStateMachine;
	 //屏幕大小
	 int m_gameWidth;
	 int m_gameHeight;
  public:
     static Game*Instance();

     bool init(const char *title, int xpos, int ypos, int width, int height, int flags);
     void render();
	 void update();
	 void handleEvents();
	 void clean();

     SDL_Renderer* getRenderer() const {return m_pRenderer;}
     bool running(){return m_bRunning;}
     void quit();
     GameStateMachine* getStateMachine();

     int getGameWidth() const
     {
         return m_gameWidth;
     }
     int getGameHeight() const
     {
         return m_gameHeight;
     }
};
typedef Game TheGame;
#endif
