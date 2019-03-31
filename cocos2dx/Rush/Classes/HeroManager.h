#ifndef __HeroManager_H__
#define __HeroManager_H__
#include<string>
#include "cocos2d.h"
#include "PosBase.h"
#include "TowerBorder.h"
#include "Monster.h"
//坑坐标的层次
#define TOWER_POS_LAYER_LVL 5
//坑的层次
#define TOWER_BORDER_LAYER_LVL 8
//塔的层次
#define TOWER_LAYER_LVL 10
USING_NS_CC;
class HeroManager : public Node
{
private:
	//存放所有坑的坐标
	Vector<PosBase*> m_towerPosList;
	//存放所有炮塔对象
	Vector<TowerBorder*> m_towerBorderList;
	//创建坑的坐标
	void createTowerPos(Point pos);
	//创建坑
	void createTowerBorder(int iCurLevel);
	//找到被单击的炮台的对象
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