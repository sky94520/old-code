#ifndef __FirePeashooter_H__
#define __FirePeashooter_H__
#include "Pea.h"

class FirePeashooter : public Pea
{
private:
	float m_duration;
	float m_elapsed;
public:
	FirePeashooter();
	~FirePeashooter();
	static FirePeashooter*create(const string&plantName);
	bool init(const string&plantName);
protected:
	virtual void updateAttackState(float dt);
	virtual void updateAttackEndState(float dt);
private:
	void changeState(State state);
};
#endif