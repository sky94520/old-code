#ifndef __Repeater_H__
#define __Repeater_H__

#include "Pea.h"

class Repeater : public Pea
{
private:
	float m_elapsed;
	int m_nCurBulletNum;
public:
	Repeater();
	~Repeater();
	static Repeater*create(const string& plantName);
	bool init(const string& plantName);
protected:
	virtual void updateAttackState(float dt);
	virtual void updateAttackEndState(float dt);
};
#endif