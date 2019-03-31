#include<vld.h>
#include "SDL_Engine/SDL_Engine.h"
#include "ThirdLayer.h"

using namespace std;
using namespace SDL;

int main(int argv,char**argc)
{
	//���ڴ����ɹ�
	if(Director::getInstance()->init("Fishing",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,480,SDL_WINDOW_SHOWN))
	{
		//�����Դ·�� ����ֲʱandroid�±���ע��
		FileUtils::getInstance()->addSearchPath("Resources");
		//��һ����������
		Director::getInstance()->runWithScene(ThirdLayer::createScene());
		Director::getInstance()->setDisplayStates(false);
		Director::getInstance()->setSecondsPerFrame(1/60.f);
		Director::getInstance()->setResolutionScale();

		while(Director::getInstance()->isRunning())
		{
			Director::getInstance()->update();
			PoolManager::getInstance()->getCurReleasePool()->clear();
		}
		Director::getInstance()->purge();
		PoolManager::getInstance()->purge();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}