#include<vld.h>

#include "SDL_Engine/SDL_Engine.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "StartScene.h"
#include "LoadingLayer.h"
#include "FlashScene.h"

using namespace std;
using namespace SDL;

int main(int argv,char**argc)
{
	//窗口创建成功
	if(Director::getInstance()->init("FishingJoy",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,960,640,SDL_WINDOW_SHOWN))
	{
		SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH,"1");
		//添加资源路径 在移植时android下必须注释
		FileUtils::getInstance()->addSearchPath("Resources");
		FileUtils::getInstance()->addSearchPath("Resources/level");
		//第一个启动场景
		Director::getInstance()->runWithScene(FlashScene::create());
		Director::getInstance()->setDisplayStates(true);
		Director::getInstance()->setSecondsPerFrame(1/60.f);
		Director::getInstance()->setResolutionScale();

		while(Director::getInstance()->isRunning())
		{
			Director::getInstance()->update();
			PoolManager::getInstance()->getCurReleasePool()->clear();
		}
		//卸载单例类
		GameScene::gameExit();

		Director::getInstance()->purge();
		PoolManager::getInstance()->purge();
	}
	//_CrtDumpMemoryLeaks();
	return 0;
}