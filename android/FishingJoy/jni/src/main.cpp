
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
	if(TheDirector::getInstance()->init("FishingJoy",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,960,640,SDL_WINDOW_SHOWN))
	{
		SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH,"1");
		//添加资源路径 在移植时android下必须注释
		//FileUtils::getInstance()->addSearchPath("Resources");
		FileUtils::getInstance()->addSearchPath("level");
		//第一个启动场景
		TheDirector::getInstance()->runWithScene(FlashScene::create());
		TheDirector::getInstance()->setDisplayStates(true);
		TheDirector::getInstance()->setSecondsPerFrame(1/60.f);
		TheDirector::getInstance()->setResolutionScale();
		//TheDirector::getInstance()->setLogicalSize();

		while(TheDirector::getInstance()->isRunning())
		{
			TheDirector::getInstance()->update();
			ThePoolManager::getInstance()->getCurReleasePool()->clear();
		}
		//卸载单例类
		GameScene::gameExit();

		Director::getInstance()->purge();
		PoolManager::getInstance()->purge();
	}
	//_CrtDumpMemoryLeaks();
	return 0;
}
