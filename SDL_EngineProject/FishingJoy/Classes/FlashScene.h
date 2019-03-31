#ifndef __FlashScene_H__
#define __FlashScene_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;

class FlashScene:public Scene
{
public:
	FlashScene();
	~FlashScene();
	CREATE_FUNC(FlashScene);
	bool init();
private:
	void preload(float dt);
};
#endif