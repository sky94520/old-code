#ifndef __Peashooter_H__
#define __Peashooter_H__
#include "Plant.h"
#include "BaseCreator.h"
class Peashooter:public Plant
{
	private:
	const static std::string NAME;
public:
	Peashooter();
	~Peashooter();
	CREATE_FUNC(Peashooter);
	bool init();

	virtual FiniteTimeAction*onNormalAction();
	virtual FiniteTimeAction*onSkillAction();
	virtual void onHurt();
	virtual void onDead();
	virtual void initInterval();
	virtual PlantType getPlantType()const;
	virtual std::string getName()const;
};
class PeashooterCreator:public BaseCreator
{
public:
	virtual ~PeashooterCreator(){}
	virtual Peashooter*createObject()const
	{
		return Peashooter::create();
	}
};
#endif