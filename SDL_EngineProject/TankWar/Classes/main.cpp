#include<vld.h>
#include "SDL_Engine/SDL_Engine.h"
#include "GameScene.h"

using namespace std;
using namespace SDL;

int main(int argv, char**argc)
{
	//���ڴ����ɹ�
	if(Director::getInstance()->init("Tank War",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,480,SDL_WINDOW_SHOWN))
	{
		//Windows�������Դ·��
		if (Director::getInstance()->getPlatform() == "Windows")
		{
			FileUtils::getInstance()->addSearchPath("Resources");
		}
		else//�������ʹ����¼�����
		{
			SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH,"1");
		}
		//������ֱͬ��
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

		//��һ����������
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
		//ϵͳ���
		Director::purge();
		//�ͷ��ڴ��
		PoolManager::getInstance()->purge();
	}

	return 0;
}