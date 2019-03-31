#include<iostream>
#ifndef __ANDROID__
#include<vld.h>
#endif
//开启调试模式 
#define _DEBUG true
#include "SDL_Engine/SDL_Engine.h"

#include "HelloWorldScene.h"

using namespace std;
using namespace SDL;
int main(int argc,char**argv)
{
	if(TheDirector::getInstance()->init("Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,600,600,SDL_WINDOW_SHOWN))
	{
		//设置成屏幕适配
		TheDirector::getInstance()->setResolutionScale();
		//第一个启动场景
		TheDirector::getInstance()->runWithScene(HelloWorld::createScene());
		TheDirector::getInstance()->setSecondsPerFrame(1/60.f);
		TheDirector::getInstance()->setDisplayStates(true);
		while(TheDirector::getInstance()->isRunning())
		{
			TheDirector::getInstance()->update();
			ThePoolManager::getInstance()->getCurReleasePool()->clear();
		}
		TheDirector::getInstance()->purgeDirector();
	}
#ifndef __ANDROID__
	_CrtDumpMemoryLeaks();
#endif
	exit(0);
}
