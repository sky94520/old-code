#ifndef __MonsterManager_H__
#define __MonsterManager_H__
#include "cocos2d.h"
USING_NS_CC;
class MonsterPos;
class Monster;
class PosBase;
//道路宽度
#define RODE_WEIGHT 4
class MonsterManager : public Node
{
private:
	Vector<Monster*> m_monsterList;
	Vector<Monster*> m_notShowMonsterList;
	//Map<int,Vector<MonsterPos*> > m_monsterPosList;//存储怪物行走路径
	Vector<PosBase*> m_monsterPosList;
	float m_fShowTimeCount;
	//检测是否有新怪物出场
	void showMonster(float dt);
public:
	MonsterManager();
	~MonsterManager();
	static MonsterManager*createWithLevel(int nLevel);
	bool initWithLevel(int nLevel);
	//获取还没有出场怪物的数量
	int getNotShowMonsterCount();
	//读取配置文件创建怪物
	void createMonsters(int nCurLevel);
	//获取怪物出场坐标
	MonsterPos*getMonsterStartPos();
	//获取怪物终点坐标
	MonsterPos*getMonsterEndPos();
	Vector<Monster*>& getMonsterList()
	{
		return m_monsterList;
	}
};
#endif