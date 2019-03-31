#ifndef __WinScene_H__
#define __WinScene_H__
#include "cocos2d.h"
USING_NS_CC;
class WinScene : public Layer
{
public:
	CREATE_FUNC(WinScene);
	virtual bool init();
	static Scene*createScene();
};
#endif