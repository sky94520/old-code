#ifndef __Magnetshroom_H__
#define __Magnetshroom_H__

#include "NightPlant.h"
class Magnetshroom : public NightPlant
{
	SDL_SYNTHESIZE(Size,m_scope,Scope);//Ó°Ïì·¶Î§
private:
	enum class State
	{
		Normal,/*Õý³£×´Ì¬*/
		Sleeping,/*Ë¯Ãß×´Ì¬*/
		AttackStart,/*¿ªÊ¼¹¥»÷×´Ì¬*/
		Attacking,/*ÕýÔÚ¹¥»÷½×¶Î*/
		Digesting,/*Ïû»¯½×¶Î*/
	};
	State m_state;
	float m_duration;
	float m_elapsed;
public:
	Magnetshroom();
	~Magnetshroom();
	static Magnetshroom*create(const string&plantName);
	bool init(const string&plantName);
protected:
	virtual void updateNotSleeping(float dt);
	virtual void onSleepingEnter();
	virtual void onSleepingExit();
private:
	void changeState(State state);

	void updateNormalState(float dt);
	void updateAttackStartState(float dt);
	void updateAttackingState(float dt);
	void updateDigestState(float dt);
};
#endif