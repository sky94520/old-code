#ifndef __PotatoMine_H__
#define __PotatoMine_H__
#include "Plant.h"
#include "BaseCreator.h"
class PotatoMine:public Plant
{
private:
	const static std::string NAME;
	SDL_BOOL_SYNTHESIZE(m_bReady,Ready);
public:
	PotatoMine();
	~PotatoMine();
	CREATE_FUNC(PotatoMine);
	bool init();

	virtual FiniteTimeAction*onNormalAction();
	virtual FiniteTimeAction*onSkillAction();
	virtual void onHurt();
	virtual void onDead();
	virtual void initInterval();
	virtual PlantType getPlantType()const;
	virtual std::string getName()const;
};
class PotatoMineCreator:public BaseCreator
{
public:
	virtual PotatoMine*createObject()const
	{
		return PotatoMine::create();
	}
};
#endif