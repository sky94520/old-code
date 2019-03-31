#ifndef __TouchLayer_H__
#define __TouchLayer_H__
#include "cocos2d.h"
USING_NS_CC;
/*抽象类，把状态传递给GameScene*/
class TouchLayerDelegate
{
public:
	virtual ~TouchLayerDelegate(){}
	virtual void arrowAimAt(const Point&pos)=0;
	virtual void arrowShootTo(const Point&pos)=0;
};
class TouchLayer:public Layer
{
private:
	TouchLayerDelegate*m_pDelegate;
public:
	TouchLayer();
	~TouchLayer();
	CREATE_FUNC(TouchLayer);
	bool init();
public:
	void setDelegate(TouchLayerDelegate*pDelegate);
public:
	virtual bool onTouchBegan(Touch*,Event*);
	virtual void onTouchMoved(Touch*touch,Event*event);
	virtual void onTouchEnded(Touch*touch,Event*event);
};
#endif