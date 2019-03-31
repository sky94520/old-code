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
	//����x������ƶ��ٶ�
	void setiXSpeed(int iSpeed);
	//����y������ƶ��ٶ�
	void setiYSpeed(int iSpeed);
private:
	int m_iXSpeed;
	int m_iYSpeed;
	//ע����Ļ�����¼�
	void registeTouchEvent();
};
#endif