#ifndef __MonsterManager_H__
#define __MonsterManager_H__
#include "cocos2d.h"
USING_NS_CC;
class MonsterPos;
class Monster;
class PosBase;
//��·���
#define RODE_WEIGHT 4
class MonsterManager : public Node
{
private:
	Vector<Monster*> m_monsterList;
	Vector<Monster*> m_notShowMonsterList;
	//Map<int,Vector<MonsterPos*> > m_monsterPosList;//�洢��������·��
	Vector<PosBase*> m_monsterPosList;
	float m_fShowTimeCount;
	//����Ƿ����¹������
	void showMonster(float dt);
public:
	MonsterManager();
	~MonsterManager();
	static MonsterManager*createWithLevel(int nLevel);
	bool initWithLevel(int nLevel);
	//��ȡ��û�г������������
	int getNotShowMonsterCount();
	//��ȡ�����ļ���������
	void createMonsters(int nCurLevel);
	//��ȡ�����������
	MonsterPos*getMonsterStartPos();
	//��ȡ�����յ�����
	MonsterPos*getMonsterEndPos();
	Vector<Monster*>& getMonsterList()
	{
		return m_monsterList;
	}
};
#endif