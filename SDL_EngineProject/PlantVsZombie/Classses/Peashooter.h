#ifndef __Peashooter_H__
#define __Peashooter_H__
#include<string>
#include "Pea.h"

using namespace std;

class Peashooter : public Pea
{
public:
	Peashooter();
	~Peashooter();
	static Peashooter*create(const string&plantName);
	bool init(const string&plantName);
protected:
	virtual void updateAttackState(float dt);
	virtual void updateAttackEndState(float dt);
};
#endif