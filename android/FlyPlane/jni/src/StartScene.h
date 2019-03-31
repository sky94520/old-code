#ifndef __StartScene_H__
#define __StartScene_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class StartScene:public Scene
{
public:
	StartScene();
	~StartScene();
	CREATE_FUNC(StartScene);
	bool init();
private:
	void gameStart(Object*sender);
	void gameEnd(Object*sender);
};
#endif