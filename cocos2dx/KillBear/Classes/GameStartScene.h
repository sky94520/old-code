#ifndef __GameStartScene_H__
#define __GameStartScene_H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
class GameStartScene : public Layer
{
public:
	GameStartScene();
	~GameStartScene();
	static Scene*createScene();
	CREATE_FUNC(GameStartScene);
	virtual bool init();
private:
	void gameStart(Ref*pRef);
	void gameEnd(Ref*pRef);
};
#endif