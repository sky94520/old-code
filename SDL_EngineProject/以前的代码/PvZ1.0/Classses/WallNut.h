#ifndef __WallNut_H__
#define __WallNut_H__
#include "Plant.h"
#include "BaseCreator.h"
typedef enum PlantStatus
{
	kPlantStatus_None,
	kPlantStatus_Carcke1,//第一临界点
	kPlantStatus_Carcke2//第二临界点
}PlantStatus;
class WallNut:public Plant
{
private:
	const static std::string NAME;
	PlantStatus m_status;
public:
	WallNut();
	~WallNut();
	CREATE_FUNC(WallNut);
	bool init();

	virtual FiniteTimeAction*onNormalAction();
	virtual FiniteTimeAction*onSkillAction();
	virtual void onHurt();
	virtual void onDead();
	virtual void initInterval();
	virtual PlantType getPlantType()const;
	virtual std::string getName()const;
};
class WallNutCreator:public BaseCreator
{
public:
	virtual WallNut*createObject()const
	{
		return WallNut::create();
	}
};
#endif