#ifndef __AboutScene_H__
#define __AboutScene_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class AboutScene:public Scene
{
public:
	AboutScene();
	~AboutScene();
	CREATE_FUNC(AboutScene);
	bool init();
private:
	void returnToStartScene(Ref*sender);
};
#endif