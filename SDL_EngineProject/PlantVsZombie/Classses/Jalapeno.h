#ifndef __Jalapeno_H__
#define __Jalapeno_H__
#include "Plant.h"

class Jalapeno : public Plant
{
	SDL_SYNTHESIZE(int,m_nDamage,Damage);
private:
	enum class State
	{
		Normal,
		Skill,
		Dying,
	};
private:
	State m_state;
	float m_elapsed;
	float m_duration;
	unsigned int m_nIndex;
public:
	Jalapeno();
	~Jalapeno();

	static Jalapeno*create(const string&plantName);
	bool init(const string& plantName);
protected:
	virtual void updateHook(float dt);
	virtual void onHurt();
	void addFire(Terrain*terrain);
	void changeState(State state);
};
#endif