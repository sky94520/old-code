#ifndef __EnemyLayer_H__
#define __EnemyLayer_H__
#include<vector>
#include "Enemy.h"
#include "SystemHeader.h"
class GameLayerDelegate;
class b2World;
class EnemyLayer:public Layer
{
private:
	std::vector<Enemy*> m_enemyList;
	GameLayerDelegate*m_pDelegate;
public:
	EnemyLayer();
	~EnemyLayer();
	CREATE_FUNC(EnemyLayer);
	bool init();
	void initEnemy(float dt);
	virtual void update(float dt); 
	void resetEnemy(Enemy*enemy);

	void setDelegate(GameLayerDelegate*pDelegate);
};
#endif