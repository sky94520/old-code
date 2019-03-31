#include<vld.h>
#include "SDL_Engine/SDL_Engine.h"
#include "HelloWorldScene.h"
#include "GameScene.h"


using namespace std;
using namespace SDL;

int main(int argv,char**argc)
{
	//窗口创建成功
	if(Director::getInstance()->init("PlantVsZombie",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,900,600,SDL_WINDOW_SHOWN))
	{
		//添加资源路径 在移植时android下必须注释
		FileUtils::getInstance()->addSearchPath("Resources");

		//第一个启动场景
		Director::getInstance()->runWithScene(GameScene::create());
		Director::getInstance()->setDisplayStates(true);
		Director::getInstance()->setSecondsPerFrame(1/60.f);
		Director::getInstance()->setResolutionScale();

		while(Director::getInstance()->isRunning())
		{
			Director::getInstance()->update();
			PoolManager::getInstance()->getCurReleasePool()->clear();
		}
		Director::getInstance()->purge();
		//释放内存池
		PoolManager::getInstance()->purge();
	}

	return 0;
}
