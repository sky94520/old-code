#ifndef __ThreeDirectionController_H__
#define __ThreeDirectionController_H__

#include "Controller.h"
#include "cocos2d.h"
USING_NS_CC;
class ThreeDirectionController :public Controller
{
public:
	CREATE_FUNC(ThreeDirectionController);
	virtual bool init();

	virtual void update(float dt);
	//设置x方向的移动速度
	void setiXSpeed(int iSpeed);
	//设置y方向的移动速度
	void setiYSpeed(int iSpeed);
private:
	int m_iXSpeed;
	int m_iYSpeed;
	//注册屏幕触摸事件
	void registeTouchEvent();
};
#endif