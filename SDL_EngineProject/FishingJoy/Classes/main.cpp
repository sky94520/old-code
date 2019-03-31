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
	//���ڴ����ɹ�
	if(Director::getInstance()->init("FishingJoy",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,960,640,SDL_WINDOW_SHOWN))
	{
		SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH,"1");
		//�����Դ·�� ����ֲʱandroid�±���ע��
		FileUtils::getInstance()->addSearchPath("Resources");
		FileUtils::getInstance()->addSearchPath("Resources/level");
		//��һ����������
		Director::getInstance()->runWithScene(FlashScene::create());
		Director::getInstance()->setDisplayStates(true);
		Director::getInstance()->setSecondsPerFrame(1/60.f);
		Director::getInstance()->setResolutionScale();

		while(Director::getInstance()->isRunning())
		{
			Director::getInstance()->update();
			PoolManager::getInstance()->getCurReleasePool()->clear();
		}
		//ж�ص�����
		GameScene::gameExit();

		Director::getInstance()->purge();
		PoolManager::getInstance()->purge();
	}
	//_CrtDumpMemoryLeaks();
	return 0;
}