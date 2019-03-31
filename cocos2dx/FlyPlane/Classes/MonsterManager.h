#ifndef __MonsterManager_H__
#define __MonsterManager_H__

#include "Monster.h"
#include "cocos2d.h"
#include "Player.h"
#include "BulletManager.h"

USING_NS_CC;

#define MAX_MONSTER 12

class MonsterManager : public Node
{
public:
	CREATE_FUNC(MonsterManager);
	virtual bool init();
	MonsterManager();
	~MonsterManager();

	virtual void update(float dt);

	void bindPlayer(Player*iPlayer);
	void bindBulletMgr(BulletManager*bulletManager);

private:
	void createMonsters();

private:
	Vector<Monster*> m_monsterArr; 
	//玩家对象，用于检测碰撞
	Player*m_player;
	//子弹管理类，用来检测碰撞
	BulletManager*m_bulletMgr;

};
#endif