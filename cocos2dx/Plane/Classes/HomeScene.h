#ifndef __HomeScene_H__
#define __HomeScene_H__
#include "cocos2d.h"
USING_NS_CC;
enum SceneType
{
	kSceneType_Game,
	kSceneType_Help,
	kSceneType_Setting
};
class HomeScene:public Scene
{
public:
	CREATE_FUNC(HomeScene);
	bool init();
private:
	void menuItemCallback(Ref*sender);
};
#endif