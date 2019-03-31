#ifndef __SingleSpriteHero_H__
#define __SingleSpriteHero_H__
#include "Hero.h"
enum EnumHeroPropConfType
{
	enHeroPropConfType_ID,
	enHeroPropConfType_Name,
	enHeroPropConfType_Type,
	enHeroPropConfType_ModelID,
	enHeroPropConfType_BaseAtk,
	enHeroPropConfType_AtkSpeed,
	enHeroPropConfType_AtkRange,
	enHeroPropConfType_UpgradeAtkBase,
	enHeroPropConfType_UpgradeCostBase,
	enHeroPropConfType_Resources,
	enHeroPropConfType_Bullet
};
class SingleSpriteHero : public Hero
{
private:
	std::string m_bulletResource;
public:
	SingleSpriteHero();
	~SingleSpriteHero();

	static SingleSpriteHero*createFromCsvFileByID(int nHeroID);
	virtual bool initWithCsvFileByID(int nHeroID);
	//action
	CC_SYNTHESIZE_RETAIN(Action*,m_pAttackAction,AttackAction);
	//override
	virtual void onDead();
	virtual void onBindSprite();
	virtual void onHurt(int nHurtValue);
};
#endif