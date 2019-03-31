#ifndef __EnemyLayer_H__
#define __EnemyLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace std;
class Enemy;
class Player;

class EnemyDelegate
{
public:
	virtual ~EnemyDelegate(){}
	virtual Player*getPlayer()const=0;
};

class EnemyLayer:public Layer
{
private:
	vector<Enemy*> m_enemys;
	EnemyDelegate*m_pDelegate;
public:
	EnemyLayer();
	~EnemyLayer();
	CREATE_FUNC(EnemyLayer);
	bool init();
	virtual void update(float dt);
	
	vector<Enemy*>& getEnemys();
	//¥¥Ω®µ–»À
	void enemyBorn(TMXObject*object,Layer*layer);
	void setDelegate(EnemyDelegate*pDelegate);
private:
	bool isObsolete(Enemy*enemy);
};
#endif