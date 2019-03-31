#ifndef __TollgateScene_H__
#define __TollgateScene_H__

#include "cocos2d.h"
#include "Player.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

using namespace cocostudio;
using namespace cocos2d::ui;

class TollgateScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void update(float delta);
    // implement the "static create()" method manually
    CREATE_FUNC(TollgateScene);
private:
	void initBG();
	//加载UI界面
	void loadUI();
	//跳跃按键回调
	void jumpEvent(Ref*,TouchEventType type);
private:
	Sprite*m_bgSprite1;
	Sprite*m_bgSprite2;

	Player*m_player;

	int m_iScore;
	Text*m_scoreLab;
	LoadingBar*m_hpBar;
};
#endif