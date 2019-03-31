#include<iostream>
//开启调试模式 
#define SDL_ENGINE_DEBUG true
#include "SDL_Engine/SDL_Engine.h"

#include "StartScene.h"

using namespace std;
using namespace SDL;
int main(int argv,char**argc)
{
	if(TheDirector::getInstance()->init("FishingJoy",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,600,360,SDL_WINDOW_SHOWN))
	{
		FileUtils::getInstance()->addSearchPath("Resources");
		//设置成屏幕适配
		TheDirector::getInstance()->setResolutionScale();
		//第一个启动场景
		TheDirector::getInstance()->runWithScene(StartScene::create());
		TheDirector::getInstance()->setSecondsPerFrame(1/60.f);
		TheDirector::getInstance()->setDisplayStates(true);
		while(TheDirector::getInstance()->isRunning())
		{
			TheDirector::getInstance()->update();
			ThePoolManager::getInstance()->getCurReleasePool()->clear();
		}
		TheDirector::getInstance()->purge();
		//释放内存池
		ThePoolManager::getInstance()->purge();
	}
	//关闭文件管理器
	FileUtils::getInstance()->purge();
	//关闭观察者
	NotificationCenter::getInstance()->purge();
	SoundManager::getInstance()->purge();
	return 0;
}
