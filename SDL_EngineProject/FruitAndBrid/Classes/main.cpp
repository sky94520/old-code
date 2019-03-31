#include<vld.h>
#include "SDL_Engine/SDL_Engine.h"
#include "MainLayer.h"
#define SDL_ENGINE_DEBUG

using namespace std;
using namespace SDL;

int main(int argv,char**argc)
{
	//���ڴ����ɹ�
	if(TheDirector::getInstance()->init("FruitAndBrid",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,540,720,SDL_WINDOW_SHOWN))
	{
		//�����Դ·�� ����ֲʱandroid�±���ע��
		FileUtils::getInstance()->addSearchPath("Resources");
		//FileUtils::getInstance()->addSearchPath("Resources/");
		//��һ����������
		TheDirector::getInstance()->runWithScene(MainLayer::createScene());
		TheDirector::getInstance()->setDisplayStates(true);
		TheDirector::getInstance()->setSecondsPerFrame(1/60.f);
		TheDirector::getInstance()->setResolutionScale();

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
	//�ر�����
	SoundManager::getInstance()->purge();
	_CrtDumpMemoryLeaks();
	return 0;
}