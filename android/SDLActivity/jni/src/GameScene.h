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
	static int PLAYER_MASKBIT;//����
	static int PLAYER_BULLET_MASKBIT;//�����ӵ�
	static int ENEMY_MASKBIT;//�л�
	static int ENEMY_BULLET_MASKBIT;//�л��ӵ�
	static int BORDER_MASKBIT;//�߽�
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
	virtual void gamePause();//��Ϸ��ͣ
	virtual void gameResume();//��Ϸ�ָ�
	virtual void gameEnd();//��Ϸ����
	virtual void gameRestart();//���¿�ʼ��Ϸ

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
private:
	void initPhysicalWorld();
};
#endif
