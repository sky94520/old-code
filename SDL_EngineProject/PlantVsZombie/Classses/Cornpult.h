#ifndef __Cornpult_H__
#define __Cornpult_H__
#include<string>
#include "Catapult.h"
using namespace std;

class Cornpult : public Catapult
{
private:
	bool m_bIsButter;//当前是否是黄油
public:
	Cornpult();
	~Cornpult();
	static Cornpult*create(const string&plantName);
	bool init(const string&plantName);
protected:
	virtual void changeState(State state);
	virtual void shoot();
	virtual void shootEndHook();
};
#endif