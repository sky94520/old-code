#ifndef __SunShroom_H__
#define __SunShroom_H__
#include "NightPlant.h"

class SunShroom : public NightPlant
{
	SDL_SYNTHESIZE(float,m_growUpTimeLeft,GrowUpTimeLeft);//�ɳ�ʣ��ʱ��
private:
	enum class State
	{
		Normal,
		Sleeping,
		Growing,
		ProducingSun
	};
private:
	State m_state;
	//���������ר��
	float m_elapsedSun;
	float m_elapsed;
	float m_duration;
	bool m_bSmall;
public:
	SunShroom();
	~SunShroom();
	static SunShroom*create(const string&plantName);
	bool init(const string&plantName);
protected:
	virtual void updateNotSleeping(float dt);
	virtual void onSleepingEnter();
	virtual void onSleepingExit();
private:
	void growUpdate(float dt);
	void productSun();
	void changeState(State state);
};
#endif