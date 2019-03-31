#include<vld.h>
#include "SDL_Engine/SDL_Engine.h"
#include "GameScene.h"
#define SDL_ENGINE_DEBUG

using namespace std;
using namespace SDL;

int main(int argv,char**argc)
{
	//���ڴ����ɹ�
	if(TheDirector::getInstance()->init("Fishing",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,480,SDL_WINDOW_SHOWN))
	{
		//�����Դ·�� ����ֲʱandroid�±���ע��
		FileUtils::getInstance()->addSearchPath("Resources");
		//��һ����������
		TheDirector::getInstance()->runWithScene(GameScene::create());
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
	//����ļ������� ����������
	FileUtils::getInstance()->purge();
	//����۲���
	NotificationCenter::getInstance()->purge();
	//�������
	SoundManager::getInstance()->purge();
	//�������ģ��
	PhysicalEngine::getInstance()->purge();

	_CrtDumpMemoryLeaks();
	return 0;
}