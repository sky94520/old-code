 #include<iostream>
#include<string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Game.h"

//全局常量
const int FPS = 60;
const int DELAY_TIME = 1000.0f/FPS;

int main(int argc,char**argv)
{
	Uint32 frameStart,frameTime;

	if (TheGame::Instance()->init("test",100,100,20 * 32,15 * 32,false))
	{
		while (TheGame::Instance()->running())
		{
			frameStart = SDL_GetTicks();

			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else
	{
	    std::cout<<"error:"<<SDL_GetError()<<std::endl;
		return -1;
	}
	TheGame::Instance()->clean();

	return 0;
}
