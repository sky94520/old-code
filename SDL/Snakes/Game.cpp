#include "Game.h"
#include "TextureManager.h"
#include "InputHandle.h"
#include "ErrorInfo.h"
#include "PlayState.h"

Game*Game::s_pInstance = NULL;

Game::Game()
{
    //默认显示FPS
	m_bFPS = true;
	//默认倍率为1
	m_fZoomTimes = 1.0;
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

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) >= 0)
	{
		/// if succeeded create our window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != NULL)
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1,SDL_RENDERER_ACCELERATED/*|SDL_RENDERER_PRESENTVSYNC*/);
		if (m_pRenderer != NULL)
		{
		    SDL_SetRenderDrawBlendMode(m_pRenderer,SDL_BLENDMODE_BLEND);
		}
		else
		return false;
	}
	else
		return false;

	m_bRunning = true;
	// init

	SDL_GetWindowSize(m_pWindow,&m_gameWidth,&m_gameHeight);

	m_gameWidth = width;
	m_gameHeight = height;
	//#endif
	/*初始化字体*/
	TTF_Init();
	/*适应屏幕*/
	suitScreen();
	/*add the code here..*/
	TheTextureManager::Instance()->bind(m_pRenderer);
	/*加载图片资源*/
	//设置刷新颜色
	SDL_SetRenderDrawColor(m_pRenderer,210,250,255,255);
	//
	m_fps = new Fps();
	//初始化状态机
	m_gameStateMachine = new GameStateMachine();
	m_gameStateMachine->pushState(new PlayState());
	return true;
}
void Game::render()
{
	///clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);
	 m_gameStateMachine->render();
	//输出fps
	if (m_bFPS == true )
	{
	    m_fps->draw(m_pRenderer);
	}
	SDL_RenderPresent(m_pRenderer);
}

void Game::handleEvents()
{
}
void Game::update()
{
    m_fps->update();
    TheInputHandle::Instance()->update();
    m_gameStateMachine->update();
}
void Game::clean()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);

	TTF_Quit();
	SDL_Quit();
}
void Game::quit()
{
    m_bRunning = false;
}
//画圆函数
SDL_Texture *Game::CreateCircleTexture(SDL_Renderer * ren, double radius,SDL_Color color)
{
  // 新建texture
  SDL_Texture *tex =
    SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                      (int )(2 * radius), (int )(2 * radius));
  // 设置叠加模式
  SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
  // SDL_SetTextureAlphaMod(tex,0);

  SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);

  // 切换渲染目标到tex
  SDL_SetRenderTarget(ren, tex);
  // 刷新tex
  SDL_RenderClear(ren);

  SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, 255);
  // 画圆
  for (double o = 0; o <= 360; o += 1)
  {
    SDL_RenderDrawPoint(ren, radius + radius * cos(o / 180 * 3.1415926),
                         radius + radius * sin(o / 180 * 3.1415926));
  }
  // 渲染目标切换回默认
  SDL_SetRenderTarget(ren, NULL);
  return tex;
}
SDL_Texture*Game::RenderText(SDL_Renderer*ren,std::string message,std::string fontFile,SDL_Color color,int fontSize)
{
    if (!TTF_WasInit())
        TTF_Init();
	TTF_Font*font = NULL;
	font = TTF_OpenFont(fontFile.c_str(),fontSize);

	if (font == NULL)
	   {
	      //ErrorInfo::Instance()->log(TTF_GetError());
	       return NULL;
	   }
	SDL_Surface*sur = TTF_RenderText_Blended(font,message.c_str(),color);
	SDL_Texture*tex = SDL_CreateTextureFromSurface(ren,sur);

	SDL_FreeSurface(sur);
	TTF_CloseFont(font);
	return tex;
}
int Game::QueryTexture(SDL_Texture*tex,Uint32*format,int*access,int*w,int*h)
{
    SDL_QueryTexture(tex,format,access,w,h);
    //缩放倍数
    *w = (*w) * m_fZoomTimes;
    *h = (*h) * m_fZoomTimes;
}
void Game::suitScreen()
{
	/*调整倍率*/
	//分辨率为xxhdpi
	if (m_gameWidth * m_gameHeight == 1080 * 1920)
	   m_fZoomTimes = 1.5;
}
