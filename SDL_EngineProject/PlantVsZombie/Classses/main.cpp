#include<vld.h>
#include "SDL_Engine/SDL_Engine.h"
#include "HelloWorldScene.h"
#include "GameScene.h"


using namespace std;
using namespace SDL;

int main(int argv,char**argc)
{
	//���ڴ����ɹ�
	if(Director::getInstance()->init("PlantVsZombie",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,900,600,SDL_WINDOW_SHOWN))
	{
		//�����Դ·�� ����ֲʱandroid�±���ע��
		FileUtils::getInstance()->addSearchPath("Resources");

		//��һ����������
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
		//�ͷ��ڴ��
		PoolManager::getInstance()->purge();
	}

	return 0;
}
