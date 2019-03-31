#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"

#include "Player.h"
#include "BulletManager.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

class GameScene : public Layer
{
public:
	GameScene();
	~GameScene();

	CREATE_FUNC(GameScene);
	virtual bool init();
	static Scene* createScene();

	virtual void update(float dt);
public:
	void initBG();
	void bulletMgrUpdate(float dt);
	
private:
	Sprite*m_bgSprite1;
	Sprite*m_bgSprite2;
	//云精灵
	Sprite*m_cloudSprite;
	//获得云
	void getCloud();

	bool m_cloudExist;
	Sprite*m_cloud1;
	Sprite*m_cloud2;
	//子弹类
	BulletManager*bulletManager;

private:
	Player*m_player;
	cocos2d::ui::Text*m_scoreUI;
};
#endif