#ifndef MonsterManager_H__
#define MonsterManager_H__
#include "Monster.h"

#define MAX_MONSTER_NUM 10

class MonsterManager : public Node
{
public:
	CREATE_FUNC(MonsterManager);
	virtual bool init();

	virtual void update(float dt);
public:
	void bindPlayer(Player*player);
private:
	void createMonsters();
private:
	Vector<Monster*> m_monsterArr;
	Player*m_player;

};
#endif