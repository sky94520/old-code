#ifndef __TiledMapAnimationTest_H__
#define __TiledMapAnimationTest_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
using namespace std;
using namespace SDL;
class TiledMapAnimationTest:public Layer
{
public:
	static Scene*createScene();

	TiledMapAnimationTest();
	~TiledMapAnimationTest();
	CREATE_FUNC(TiledMapAnimationTest);
	bool init();
};
#endif