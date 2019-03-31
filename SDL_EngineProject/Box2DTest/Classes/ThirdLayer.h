#ifndef __ThirdLayer_H__
#define __ThirdLayer_H__
#include "SDL_Engine/SDL_Engine.h"

USING_NS_SDL;

class ThirdLayer : public Layer
{
public:
	ThirdLayer();
	~ThirdLayer();

	static Scene* createScene();
	CREATE_FUNC(ThirdLayer);
	bool init();
};
#endif