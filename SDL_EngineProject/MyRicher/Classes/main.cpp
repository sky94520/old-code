#include<vld.h>
#include "SDL_Engine/SDL_Engine.h"
#include "HelloWorldScene.h"
#include "GameScene.h"

using namespace std;
using namespace SDL;

int main(int argv,char**argc)
{
	//窗口创建成功
	if(TheDirector::getInstance()->init("RPG",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,480,SDL_WINDOW_SHOWN))
	{
		//添加资源路径 在移植时android下必须注释
		FileUtils::getInstance()->addSearchPath("Resources");

		//第一个启动场景
		TheDirector::getInstance()->runWithScene(GameScene::getInstance());
		//TheDirector::getInstance()->runWithScene(HelloWorld::createScene());
		TheDirector::getInstance()->setDisplayStates(true);
		TheDirector::getInstance()->setSecondsPerFrame(1/60.f);
		TheDirector::getInstance()->setResolutionScale();

		while(TheDirector::getInstance()->isRunning())
		{
			TheDirector::getInstance()->update();
			ThePoolManager::getInstance()->getCurReleasePool()->clear();
		}
		GameScene::purge();
		//系统清除
		TheDirector::getInstance()->purge();
		//释放内存池
		ThePoolManager::getInstance()->purge();
	}

	return 0;
}