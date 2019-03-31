#ifndef __NightPlant_H__
#define __NightPlant_H__

#include "Plant.h"

class NightPlant : public Plant
{
private:
	bool m_bSleeping;//当前是否正在睡眠
public:
	NightPlant();
	~NightPlant();
	//进入睡眠
	void enterSleeping();
	//退出睡眠
	void exitSleeping();
	//更新
	virtual void updateHook(float dt);
	//当前植物是否正在睡觉
	bool isSleeping()const;
protected:
	//不睡觉更新函数
	virtual void updateNotSleeping(float dt)=0;
	virtual void onSleepingEnter()=0;
	virtual void onSleepingExit()=0;
};
#endif