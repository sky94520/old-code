#include<iostream>
#include<string>

#include "String.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "ErrorInfo.hpp"

#include "Game.h"
#include "Game.cpp"
// 全局常量
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char **argv)
{
	Uint32 frameStart, frameTime;
	//init
	try
	{
	TheGame::Instance()->init("Chapter 5", 100, 100, 640, 800, false);
	}
	catch (String s)
	{
		TheErrorInfo::Instance()->log(s.c_str());
	}
	TheErrorInfo::Instance()->log("初始化成功");

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
	TheGame::Instance()->clean();

	return 0;
}
