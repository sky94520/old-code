#ifndef __PotatoMine_H__
#define __PotatoMine_H__
#include<string>
#include "Plant.h"
using namespace std;

class PotatoMine : public Plant
{
private:
	enum class State
	{
		Ready,/*׼��*/
		ReadySuccess,/*׼�����*/
		Rising,/*������������*/
	};
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//�˺�ֵ
private:
	State m_state;
	float m_elapsed;
	float m_duration;
public:
	PotatoMine();
	~PotatoMine();
	static PotatoMine*create(const string&plantName);
	bool init(const string&plantName);

	virtual void updateHook(float dt);
private:
	void readySuccess();
	void checkCollision();
	void changeState(State state);
};
#endif