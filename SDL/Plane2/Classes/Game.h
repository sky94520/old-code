#ifndef __Game_H__
#define __Game_H__

#include<vector>
#include<iostream>

#include "SDL2/SDL.h"

#include "GameStateMachine.h"

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
	 //当前关卡
	 int m_currentLevel;
	 //玩家生命
	 int m_playerLives;
	 //当前关卡是否通关
	 bool m_bLevelComplete;
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
     int getCurrentLevel() const
     {
     	return m_currentLevel;
     }
     void setCurrentLevel(int currentLevel)
     {
     	m_currentLevel = currentLevel;
     	//m_pGameStateMachine->changeState(new BetweenLevelState());
     	m_bLevelComplete = false;
     }
     int getPlayerLives()
     {
     	return m_playerLives;
     }
     void setPlayerLives(int playerLives)
     {
     	m_playerLives = playerLives;
     }
     bool getLevelComplete()
     {
     	return m_bLevelComplete;
     }
     int getScrollSpeed()
     {
     	return 3;
     }
};
typedef Game TheGame;
#endif
