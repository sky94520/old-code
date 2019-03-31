#ifndef __GameScene_H__
#define __GameScene_H__
#include "cocos2d.h"
#include "TouchLayer.h"
#include "GameLayer.h"
#include "HelpLayer.h"
#include "PauseLayer.h"
#include "PanelLayer.h"
#include "DefeatLayer.h"
#include "SuccessLayer.h"

#include "Box2D/Box2D.h"
class Fish;
class Fork;
class FishLayer;

USING_NS_CC;
enum GameState
{
	kOperateResume = 0,
	kOperatePause = 1
};
class GameScene:public Scene,public TouchLayerDelegate,HelpLayerDelegate
	,PanelLayerDelegate,PauseLayerDelegate,DefeatLayerDelegate,SuccessLayerDelegate
	,b2ContactListener
{
private:
	TouchLayer*m_pTouchLayer;//事件分发层
	HelpLayer*m_pHelpLayer;//捕鱼帮助层
	PanelLayer*m_pPanelLayer;//面板层
	GameLayer*m_pGameLayer;//游戏层
	FishLayer*m_pFishLayer;//鱼层
	PauseLayer*m_pPauseLayer;//暂停层
	DefeatLayer*m_pDefeatLayer;//失败层
	SuccessLayer*m_pSuccessLayer;

	int m_nCurLevel;//当前关卡

	CustomCommand _command;
public:
	GameScene();
	~GameScene();
	static GameScene*create(int level);

	bool init(int level);

	virtual void update(float dt);
	//加载关卡脚本 并重置
	void loadLevel(const std::string&filename);
private:
	//叉子
	virtual void shoot(const Point&targetPos);

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

	virtual Vector<Fish*>* getShowingFishes();
	virtual Fork*getShowingFork();

	virtual bool isClickComponents(const Point&pos);

	virtual void gamePause();//游戏暂停
	virtual void gameResume();//游戏恢复
	virtual void gameRestart();//游戏重新开始
	virtual void nextLevel();//进行下一关
	virtual void showQuestionLayer();

	virtual void turnToLevelLayer();//跳转到关卡选择界面

	void operateAllSchedulerAndActions(Node*node,int flag);
private:
	virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags);
	void onDraw(const Mat4 &transform, uint32_t flags);
};
#endif