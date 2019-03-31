 #include<iostream>
#include<string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Game.h"
#include "Game.cpp"
//全局常量
const int FPS = 60;
const int DELAY_TIME = 1000.0f/FPS;

int main(int argc,char**argv)
{
	Uint32 frameStart,frameTime;

	if (Game::Instance()->init("Chapter 5",100,100,640,480,false))
	{
		while (Game::Instance()->running())
		{
			frameStart = SDL_GetTicks();

			Game::Instance()->handleEvents();
			Game::Instance()->update();
			Game::Instance()->render();

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
	Game::Instance()->clean();

	return 0;
}
