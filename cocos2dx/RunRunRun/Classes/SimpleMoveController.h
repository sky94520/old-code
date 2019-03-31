#ifndef __SimpleMoveController_H__
#define __SimpleMoveController_H__

#include "cocos2d.h"
#include "Controller.h"
USING_NS_CC;

class SimpleMoveController : public Controller
{
public:
	CREATE_FUNC(SimpleMoveController);
	virtual bool init();
	virtual void update(float dt);
	//设置移动速度
	void setiSpeed(int iSpeed);
private:
	int m_iSpeed;
};
#endif