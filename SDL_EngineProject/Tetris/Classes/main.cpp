#include<vld.h>
#include "SDL_Engine/SDL_Engine.h"
#include "GameScene.h"

#define SDL_ENGINE_DEBUG

using namespace std;
using namespace SDL;

int main(int argv,char**argc)
{
	//���ڴ����ɹ�
	if(TheDirector::getInstance()->init("Tetris",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,480,640,SDL_WINDOW_SHOWN))
	{
		SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH,"1");
		//�����Դ·�� ����ֲʱandroid�±����޸�
		FileUtils::getInstance()->addSearchPath("Resources");
		FileUtils::getInstance()->addSearchPath("Resources/music");
		//FileUtils::getInstance()->addSearchPath("Resources/");
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
	_CrtDumpMemoryLeaks();
	return 0;
}