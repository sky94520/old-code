#ifndef __TouchLayer_H__
#define __TouchLayer_H__
#include "cocos2d.h"
USING_NS_CC;
class TouchLayerDelegate
{
public:
	virtual ~TouchLayerDelegate(){}
	virtual void shoot(const Point&targetPos) = 0;
	virtual bool isClickComponents(const Point&pos)=0;
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
	virtual bool onTouchBegan(Touch*touch,Event*event);
	virtual void onTouchMoved(Touch*touch,Event*event);
	virtual void onTouchEnded(Touch*touch,Event*event);

	void setDelegate(TouchLayerDelegate*pDelegate);
};
#endif