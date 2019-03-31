#ifndef __SunFlower_H__
#define __SunFlower_H__
#include "Plant.h"
#include "BaseCreator.h"
class SunFlower:public Plant
{
private:
	const static std::string NAME;
public:
	SunFlower();
	~SunFlower();
	CREATE_FUNC(SunFlower);
	bool init();

	virtual FiniteTimeAction*onNormalAction();
	virtual FiniteTimeAction*onSkillAction();
	virtual void onHurt();
	virtual void onDead();
	virtual void initInterval();
	virtual PlantType getPlantType()const;
	virtual std::string getName()const;
};
//Ì«Ñô»¨´´ÔìÆ÷
class SunFlowerCreator:public BaseCreator
{
public:
	virtual SunFlower*createObject()const
	{
		return SunFlower::create();
	}
};
#endif