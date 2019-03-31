#include<iostream>
//��������ģʽ 
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
		//���ó���Ļ����
		TheDirector::getInstance()->setResolutionScale();
		//��һ����������
		TheDirector::getInstance()->runWithScene(StartScene::create());
		TheDirector::getInstance()->setSecondsPerFrame(1/60.f);
		TheDirector::getInstance()->setDisplayStates(true);
		while(TheDirector::getInstance()->isRunning())
		{
			TheDirector::getInstance()->update();
			ThePoolManager::getInstance()->getCurReleasePool()->clear();
		}
		TheDirector::getInstance()->purge();
		//�ͷ��ڴ��
		ThePoolManager::getInstance()->purge();
	}
	//�ر��ļ�������
	FileUtils::getInstance()->purge();
	//�رչ۲���
	NotificationCenter::getInstance()->purge();
	SoundManager::getInstance()->purge();
	return 0;
}
