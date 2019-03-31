#ifndef __BeginScene_H__
#define __BeginScene_H__
#include "cocos2d.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace cocostudio;

USING_NS_CC;
class BeginScene : public Layer
{
public:
	static Scene*createScene();
	virtual bool init();
	CREATE_FUNC(BeginScene);

private:
	void clickBeginBtn(Ref*,TouchEventType type);
	void clickModeBtn(Ref*,TouchEventType type);
	void clickAboutBtn(Ref*,TouchEventType type);
	void clickExitBtn(Ref*,TouchEventType type);
};
#endif