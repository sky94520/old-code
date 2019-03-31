#ifndef __CherryBoom_H__
#define __CherryBoom_H__
#include "Plant.h"
#include "BaseCreator.h"
class CherryBomb:public Plant
{
private:
	const static std::string NAME;
public:
	CherryBomb();
	~CherryBomb();
	CREATE_FUNC(CherryBomb);
	bool init();

	virtual FiniteTimeAction*onNormalAction();
	virtual FiniteTimeAction*onSkillAction();
	virtual void onHurt();
	virtual void onDead();
	virtual void initInterval();
	virtual PlantType getPlantType()const;
	virtual std::string getName()const;
};
class CherryBombCreator:public BaseCreator
{
public:
	virtual CherryBomb*createObject()const
	{
		return CherryBomb::create();
	}
};
#endif