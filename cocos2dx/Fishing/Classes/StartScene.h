#ifndef __StartScene_H__
#define __StartScene_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class StartScene:public Scene
{
public:
	StartScene();
	~StartScene();
	CREATE_FUNC(StartScene);
	bool init();
private:
	void gameStart(Ref*sender);
	void gameHelpLayer(Ref*sender);
	void gameExit(Ref*sender);
};
#endif