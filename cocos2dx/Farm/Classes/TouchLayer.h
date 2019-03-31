#ifndef __TouchLayer_H__
#define __TouchLayer_H__
#include "cocos2d.h"
USING_NS_CC;
class TouchLayerDelegate
{
public:
	~TouchLayerDelegate(){}
	virtual void operateBackground(const std::vector<Touch*>&touches,Event*event)=0;
	virtual void setScaleForBackground(EventMouse*event)=0;
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

	void setDelegate(TouchLayerDelegate*pDelegate);

	virtual void onTouchesBegan(const std::vector<Touch*>& touches,Event*event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *event);

	virtual void onMouseScroll(EventMouse*event);
};
#endif