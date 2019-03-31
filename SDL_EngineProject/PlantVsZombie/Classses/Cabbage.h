#ifndef __Cabbage_H__
#define __Cabbage_H__
#include "Catapult.h"
class ZombieBase;

class Cabbage : public Catapult
{
public:
	Cabbage();
	~Cabbage();
	static Cabbage*create(const string&plantName);
	bool init(const string&plantName);
protected:
	virtual void changeState(State state);
	virtual void shoot();
	virtual void shootEndHook();
};
#endif