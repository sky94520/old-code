#ifndef __Hero_H__
#define __Hero_H__
#include "Entity.h"
#include "Monster.h"
class Hero : public Entity
{
private:
	void onDraw(const kmMat4 &transform,bool transformUpdated);
	CustomCommand _customCommand;
protected:
	// the resource of sprite
	std::string FILE_PATH;
protected:
	std::string m_resource;
	//lock the monster
	Monster*m_pAtkMonster;
	//whether can attack
	bool m_bIsCanAttack;
public:
	Hero();
	~Hero();
	//static Hero*createFromCsvFileByID(int nHeroID);
	virtual bool initWithCsvFileByID(int nHeroID);

	CC_SYNTHESIZE(int,m_nBaseAtk,BaseAtk);//基础攻击力
	CC_SYNTHESIZE(int,m_nCurAtk,CurAtk);//当前攻击力
	CC_SYNTHESIZE(float,m_nAtkSpeed,AtkSpeed);//攻击速度
	CC_SYNTHESIZE(int,m_nAtkRange,AtkRange);//攻击范围
	CC_SYNTHESIZE(int,m_nUpgradeCostBase,UpgradeCostBase);//升级消耗
	CC_SYNTHESIZE(float,m_fUpgradeAtkBase,UpgradeAtkBase);//攻击力加成系数
	//logic
	void logic(float dt,Vector<Monster*>& monsterList);
	//attack,different class have diferent method
	virtual void attack();
	//check the locked monster is out of range
	void checkAimIsOutOfRange(Vector<Monster*> monsterList);
	//check one monster is in attack range
	bool isInAtkRange(Point pos);
	//choose one monster
	void chooseAim(Vector<Monster*>& monsterList);
	//draw the attack range
	virtual void draw(Renderer*renderer,const kmMat4 &,uint32_t flags);
	void attackEnd(float);
	//override
	virtual void onBindSprite();
};
#endif