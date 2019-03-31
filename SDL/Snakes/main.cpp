#include<string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Game.h"

int main(int argc,char**argv)
{
	if (TheGame::Instance()->init("贪吃蛇by小牛_牛sky",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,900,600,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL))
	{
	    //展示fps信息
	    TheGame::Instance()->isShowFPS(true);

		while (TheGame::Instance()->running())
		{
			TheGame::Instance()->update();
			TheGame::Instance()->render();
			TheGame::Instance()->handleEvents();
		}
	}
	else
	{
	    //std::cout<<"error:"<<SDL_GetError()<<std::endl;
		return -1;
	}
	TheGame::Instance()->clean();

	return 0;
}
