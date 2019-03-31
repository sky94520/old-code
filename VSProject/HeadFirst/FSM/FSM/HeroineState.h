#ifndef __HeroineState_H__
#define __HeroineState_H__
#include "SystemUtils.h"
class Heroine;

class HeroineState
{
public:
	virtual ~HeroineState(){}
	virtual void handleInput(Heroine*heroine,Input input)=0;
	virtual void update(Heroine*heroine)=0;
};
class DuckingState:public HeroineState
{
private:
	float changeTime;
public:
	DuckingState();
	virtual void handleInput(Heroine*heroine,Input input);
	virtual void update(Heroine*heroine);
};
#endif