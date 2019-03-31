#ifndef __HeroManager_H__
#define __HeroManager_H__
#include<string>
#include "cocos2d.h"
#include "PosBase.h"
#include "TowerBorder.h"
#include "Monster.h"
//������Ĳ��
#define TOWER_POS_LAYER_LVL 5
//�ӵĲ��
#define TOWER_BORDER_LAYER_LVL 8
//���Ĳ��
#define TOWER_LAYER_LVL 10
USING_NS_CC;
class HeroManager : public Node
{
private:
	//������пӵ�����
	Vector<PosBase*> m_towerPosList;
	//���������������
	Vector<TowerBorder*> m_towerBorderList;
	//�����ӵ�����
	void createTowerPos(Point pos);
	//������
	void createTowerBorder(int iCurLevel);
	//�ҵ�����������̨�Ķ���
	TowerBorder*findClickTowerBorder(Point pos);
public:
	HeroManager();
	~HeroManager();
	static HeroManager*createWithLevel(int nCurLevel);
	bool initWithLevel(int nCurLevel);
	//execute the logic code
	void logic(float dt,Vector<Monster*>& monsterList);
};
#endif