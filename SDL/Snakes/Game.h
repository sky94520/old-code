#ifndef __Game_H__
#define __Game_H__

#include<vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "Fps.h"
#include "GameStateMachine.h"

class Game
{
  private:
     Game();
     //SDL窗口 渲染器
     SDL_Window*m_pWindow;
     SDL_Renderer*m_pRenderer;
     //是否运行
     bool m_bRunning;

	 static Game*s_pInstance;
	 //是否输出fps等信息，默认为输出
	 bool m_bFPS;
	 Fps*m_fps;
	 //屏幕大小
	 int m_gameWidth;
	 int m_gameHeight;
	 
	 //游戏缩放倍数,默认为1
	 float m_fZoomTimes;
	 //状态机
	 GameStateMachine*m_gameStateMachine;
  private:
     //适应屏幕
     void suitScreen();
  public:
     static Game*Instance();
     //初始化
     bool init(const char *title, int xpos, int ypos, int width, int height, int flags);
     void render();
	 void update();
	 void handleEvents();
	 void clean();

     SDL_Renderer* getRenderer() const {return m_pRenderer;}
     //运行是否结束
     bool running(){return m_bRunning;}
     //退出
     void quit();

     int getGameWidth() const
     {
         return m_gameWidth;
     }
     int getGameHeight() const
     {
         return m_gameHeight;
     }
     //刷新窗口尺寸
     void updateWindowSize()
     {
     	SDL_GetWindowSize(m_pWindow,&m_gameWidth,&m_gameHeight);
     }
     //重写SDL_QueryTexture(),但受到倍率的影响
     int QueryTexture(SDL_Texture*tex,Uint32*format,int*access,int*w,int*h);
     void isShowFPS(bool f)
     {
     	m_bFPS = f;
     }
     const float getZoomTimes() const
     {
         return m_fZoomTimes;
     }
     //创建颜色圆
     SDL_Texture *CreateCircleTexture(SDL_Renderer * ren, double radius,SDL_Color color);
  /* 输出字体 */
  SDL_Texture *RenderText(SDL_Renderer * ren, std::string message,
                          std::string fontFile, SDL_Color color, int fontSize);
};
typedef Game TheGame;
#endif