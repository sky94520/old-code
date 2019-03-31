#ifndef __Pumpkin_H__
#define __Pumpkin_H__
#include "Defender.h"

class Pumpkin : public Defender
{
private:
	enum class State
	{
		None,
		Normal,
		Damage1,
		Damage2,
	};
private:
	State m_state;
public:
	Pumpkin();
	~Pumpkin();
	static Pumpkin*create(const string& plantName);
	bool init(const string& plantName);
protected:
	virtual void updateHook(float dt);
	virtual void onHurt();
private:
	virtual void changeState(State state);
};
#endif