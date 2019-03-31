#ifndef __CannonsHero_H__
#define __CannonsHero_H__
#include "Hero.h"
#include "Bullet.h"
enum EnumCannonsHeroPropConfType
{
	enCannonsHeroPropConfType_ID,
	enCannonsHeroPropConfType_Name,
	enCannonsHeroPropConfType_Type,
	enCannonsHeroPropConfType_ModelID,
	enCannonsHeroPropConfType_BaseAtk,
	enCannonsHeroPropConfType_AtkSpeed,//5
	enCannonsHeroPropConfType_AtkRange,//6
	enCannonsHeroPropConfType_UpgradeCostBase,//7
	enCannonsHeroPropConfType_Resources,
	enCannonsHeroPropConfType_Bullet,
	enCannonsHeroPropConfType_AllAttackNum,
	enCannonsHeroPropConfType_AttackNum,
	enCannonsHeroPropConfType_refillNum
};
class CannonsHero : public Hero
{
private:
	std::string m_initSpriteName;
	Bullet*m_pBullet;
protected:
	void attackCallBack();
public:
	CannonsHero();
	~CannonsHero();

	static CannonsHero*createFromCsvFileByID(int nHeroID);
	virtual bool initWithCsvFileByID(int nHeroID);
	//action
	CC_SYNTHESIZE_RETAIN(Action*,m_pAttackAction,AttackAction);
	//override
	virtual void attack();
	virtual void onDead();
	virtual void onBindSprite();
	virtual void onHurt(int nHurtValue);
};
#endif