#ifndef __NightPlant_H__
#define __NightPlant_H__

#include "Plant.h"

class NightPlant : public Plant
{
private:
	bool m_bSleeping;//��ǰ�Ƿ�����˯��
public:
	NightPlant();
	~NightPlant();
	//����˯��
	void enterSleeping();
	//�˳�˯��
	void exitSleeping();
	//����
	virtual void updateHook(float dt);
	//��ǰֲ���Ƿ�����˯��
	bool isSleeping()const;
protected:
	//��˯�����º���
	virtual void updateNotSleeping(float dt)=0;
	virtual void onSleepingEnter()=0;
	virtual void onSleepingExit()=0;
};
#endif