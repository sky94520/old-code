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
     //SDL�Ĵ��ڼ���Ⱦ��
     SDL_Window*m_pWindow;
     SDL_Renderer*m_pRenderer;
     //�Ƿ��˳���Ϸѭ��
     bool m_bRunning;
     //������
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