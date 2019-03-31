#ifndef __EnemyLayer_H__
#define __EnemyLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "Plane.h"

using namespace std;
using namespace SDL;
class Plane;
class Enemy;
class EnemyLayerDelegate
{
public:
	virtual ~EnemyLayerDelegate(){}
	virtual void shooting(Plane*plane,BulletType type)=0;
};
/*敌机管理者，负责产生和销毁敌机*/
class EnemyLayer:public Layer,public PlaneDelegate
{
private:
	vector<Enemy*> m_enemies;
	 Plane*m_pPlayer;//对主角的引用
	 Sprite*m_pTower;

	 EnemyLayerDelegate*m_pDelegate;
	 //每几次，炮塔都会更换位置
	 int m_nChangePos;
public:
	EnemyLayer();
	~EnemyLayer();
	static EnemyLayer*create(Plane*player,EnemyLayerDelegate*pDelegate);
	bool init( Plane*player,EnemyLayerDelegate*pDelegate);

	Enemy*createEnemy();
	virtual void update(float dt);
	void reset();
private:
	virtual void shooting(Plane*plane,BulletType type);
	void setEnemyRotation(Enemy*enemy);
	void updateTowerState();
};
#endif