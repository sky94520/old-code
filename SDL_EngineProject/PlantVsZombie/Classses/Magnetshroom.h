#ifndef __Magnetshroom_H__
#define __Magnetshroom_H__

#include "NightPlant.h"
class Magnetshroom : public NightPlant
{
	SDL_SYNTHESIZE(Size,m_scope,Scope);//Ӱ�췶Χ
private:
	enum class State
	{
		Normal,/*����״̬*/
		Sleeping,/*˯��״̬*/
		AttackStart,/*��ʼ����״̬*/
		Attacking,/*���ڹ����׶�*/
		Digesting,/*�����׶�*/
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