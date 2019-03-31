#ifndef __Monster_H__
#define __Monster_H__
#include<cmath>
#include "Entity.h"
#include "HpBar.h"
class PosBase;
enum EnumMonsterPropConfType
{
	enMonsterPropConfType_ID,
	enMonsterPropConfType_Name,
	enMonsterPropConfType_Level,
	enMonsterPropConfType_Type,
	enMonsterPropConfType_ModelID,
	enMonsterPropConfType_Defense,
	enMonsterPropConfType_Hp,
	enMonsterPropConfType_Speed,
	enMonsterPropConfType_Resources,
	// frames
	enMonsterPropConfType_Up,
	enMonsterPropConfType_Down,
	enMonsterPropConfType_Horizontal,
	enMonsterPropConfType_Attack,
	enMonsterPropConfType_Dead
};
//action
enum EnumMonsterActionType
{
	enActionType_up,
	enActionType_down,
	enActionType_horizontal,
	enActionType_attack,
	enActionType_dead
};
//frames
typedef struct
{
	int up;
	int down;
	int horizontal;
	int attack;
	int dead;
}MonsterFrame;
//Ĭ��·�����
#define RODE_WEIGHT 20
class Monster : public Entity
{
private:
	//���ƫ����
	int m_nRandonOffsetX;
	//per time to handle
	int m_nMoveTimeCount;
	//��ǰ�ڼ��������
	int m_nLocation;
	//����
	Vector<PosBase*> m_monsterPosList;
	//hp bar
	HpBar*m_pHpBar;
	//picture resource
	std::string m_resource;
	//frames
	MonsterFrame m_monsterFrame;
	//current state
	EnumMonsterActionType m_type;

	CC_SYNTHESIZE(int,m_nLevel,Level);
	CC_SYNTHESIZE(float,m_fShowTime,ShowTime);
	//action
	CC_SYNTHESIZE_RETAIN(Action*,m_pUpWalkAction,UpWalkAction);
	CC_SYNTHESIZE_RETAIN(Action*,m_pDownWalkAction,DownWalkAction);
	CC_SYNTHESIZE_RETAIN(Action*,m_pHorizontalWalkAction,HorizontalWalkAction);
	//CC_SYNTHESIZE_RETAIN(Action*,m_pAttackAction,AttackAction);
	CC_SYNTHESIZE_RETAIN(Action*,m_pDeadAction,DeadAction);
public:
	Monster();
	~Monster();
	
	static Monster*createFromCsvFileByID(int nMonsterID);
	bool initFromCsvFileByID(int nMonsterID);
	//���ո�����������ƶ�
	void moveByPosList(Vector<PosBase*>& posList);

	void updateSelf(float dt);
	void hurtMe(int nHurtValue);
	//override
	virtual void onDead();
	virtual void onHurt(int nHurtValue);
	virtual void onBindSprite();
	//action
private:
	bool changeState(EnumMonsterActionType type);
public:
	void runUpWalkAction();
	void runDownWalkAction();
	void runHorizontalWalkAction();
	void runAttackAction();
	void runDeadAction();
};
#endif