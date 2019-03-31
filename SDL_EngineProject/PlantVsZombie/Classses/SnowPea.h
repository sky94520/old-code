#ifndef __SnowPea_H__
#define __SnowPea_H__
#include<string>
#include "Peashooter.h"
using namespace std;

class SnowPea : public Peashooter
{
public:
	SnowPea();
	~SnowPea();
	static SnowPea*create(const string&plantName);
	bool init(const string&plantName);
protected:
	virtual void updateAttackState(float dt);
	virtual void updateAttackEndState(float dt);
};
#endif