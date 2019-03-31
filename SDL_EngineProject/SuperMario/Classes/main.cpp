#include<vld.h>
#include "SDL_Engine/SDL_Engine.h"
#include "GameScene.h"
#include "HelloWorldScene.h"

using namespace std;
using namespace SDL;

int main(int argv,char**argc)
{
	//窗口创建成功
	if(TheDirector::getInstance()->init("SuperMario",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,480,SDL_WINDOW_SHOWN))
	{
		//设置触碰和鼠标分离
		SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH,"1");
		//添加资源路径 在移植时android下必须注释
		FileUtils::getInstance()->addSearchPath("Resources");
		//第一个启动场景
		TheDirector::getInstance()->runWithScene(GameScene::create());
		//TheDirector::getInstance()->runWithScene(HelloWorld::createScene());
		TheDirector::getInstance()->setDisplayStates(true);
		TheDirector::getInstance()->setSecondsPerFrame(1/60.f);
		TheDirector::getInstance()->setResolutionScale();

		while(TheDirector::getInstance()->isRunning())
		{
			TheDirector::getInstance()->update();
			ThePoolManager::getInstance()->getCurReleasePool()->clear();
		}
		Director::getInstance()->purge();
		PoolManager::getInstance()->purge();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}