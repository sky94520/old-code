#ifndef __TouchController_H__
#define __TouchController_H__
#include "cocos2d.h"
#include "TouchListener.h"

class TouchController : public cocos2d::Node
{
public:
	CREATE_FUNC(TouchController);
	virtual bool init();

	void handleTouchEvent();
	void setTouchListener(TouchListener*iTouchListener);
private:
	TouchListener*m_touchListener;
};
#endif