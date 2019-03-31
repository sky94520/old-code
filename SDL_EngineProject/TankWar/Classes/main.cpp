#include<vld.h>
#include "SDL_Engine/SDL_Engine.h"
#include "GameScene.h"

using namespace std;
using namespace SDL;

int main(int argv, char**argc)
{
	//窗口创建成功
	if(Director::getInstance()->init("Tank War",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,480,SDL_WINDOW_SHOWN))
	{
		//Windows下添加资源路径
		if (Director::getInstance()->getPlatform() == "Windows")
		{
			FileUtils::getInstance()->addSearchPath("Resources");
		}
		else//设置鼠标和触碰事件分离
		{
			SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH,"1");
		}
		//开启垂直同步
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

		//第一个启动场景
		Director::getInstance()->runWithScene(GameScene::getInstance());
		Director::getInstance()->setDisplayStates(true);
		Director::getInstance()->setSecondsPerFrame(1/60.f);
		Director::getInstance()->setResolutionScale();

		while(Director::getInstance()->isRunning())
		{
			Director::getInstance()->update();
			PoolManager::getInstance()->getCurReleasePool()->clear();
		}
		GameScene::purge();
		//系统清除
		Director::purge();
		//释放内存池
		PoolManager::getInstance()->purge();
	}

	return 0;
}