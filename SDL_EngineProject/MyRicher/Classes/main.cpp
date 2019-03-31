#include<vld.h>
#include "SDL_Engine/SDL_Engine.h"
#include "HelloWorldScene.h"
#include "GameScene.h"

using namespace std;
using namespace SDL;

int main(int argv,char**argc)
{
	//���ڴ����ɹ�
	if(TheDirector::getInstance()->init("RPG",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,480,SDL_WINDOW_SHOWN))
	{
		//�����Դ·�� ����ֲʱandroid�±���ע��
		FileUtils::getInstance()->addSearchPath("Resources");

		//��һ����������
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
		//ϵͳ���
		TheDirector::getInstance()->purge();
		//�ͷ��ڴ��
		ThePoolManager::getInstance()->purge();
	}

	return 0;
}