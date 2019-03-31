#ifndef __GameScene_H__
#define __GameScene_H__
#include "SDL_Engine/SDL_Engine.h"
#include "OperateLayer.h"
#include "BulletLayer.h"
#include "Plane.h"
#include "PlayerLayer.h"
#include "EnemyLayer.h"
#include "GameOverLayer.h"

using namespace SDL;
class PanelLayer;

class GameScene:public Scene,public OperateLayerDelegate,public PlayerLayerDelegate
	,public EnemyLayerDelegate,public GameOverDelegate
	,public b2ContactListener
{
public:
	static int PLAYER_MASKBIT;//主角
	static int PLAYER_BULLET_MASKBIT;//主角子弹
	static int ENEMY_MASKBIT;//敌机
	static int ENEMY_BULLET_MASKBIT;//敌机子弹
	static int BORDER_MASKBIT;//边界
private:
	OperateLayer*m_pOperateLayer;
	PlayerLayer*m_pPlayerLayer;
	BulletLayer*m_pBulletLayer;
	EnemyLayer*m_pEnemyLayer;
	PanelLayer*m_pPanelLayer;
	GameOverLayer*m_pGameOverLayer;
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();

	virtual void update(float dt);
private:
	virtual void degreeUpdate(const Point&degree);
	virtual void wantShooting();

	virtual void shooting(Plane*plane,BulletType type);
	virtual void gamePause();//游戏暂停
	virtual void gameResume();//游戏恢复
	virtual void gameEnd();//游戏结束
	virtual void gameRestart();//重新开始游戏

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
private:
	void initPhysicalWorld();
};
#endif
