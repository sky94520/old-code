#include<vld.h>
#include "SDL_Engine/SDL_Engine.h"
#include "GameScene.h"
#include "HelloWorldScene.h"

using namespace std;
using namespace SDL;

int main(int argv,char**argc)
{
	//���ڴ����ɹ�
	if(TheDirector::getInstance()->init("SuperMario",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,480,SDL_WINDOW_SHOWN))
	{
		//���ô�����������
		SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH,"1");
		//�����Դ·�� ����ֲʱandroid�±���ע��
		FileUtils::getInstance()->addSearchPath("Resources");
		//��һ����������
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