#ifndef __TouchLayer_H__
#define __TouchLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
/*�����࣬��״̬���ݸ�GameScene*/
class TouchLayerDelegate
{
public:
	virtual ~TouchLayerDelegate(){}
	virtual void cannonAimAt(const Point&target)=0;
	virtual void cannonShootTo(const Point&target)=0;
	virtual void  chooseBullet(const Point&pos)=0;
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
	virtual bool onTouchBegan(Touch*,SDL_Event*);
	virtual void onTouchMoved(Touch*touch,SDL_Event*event);
	virtual void onTouchEnded(Touch*touch,SDL_Event*event);
};
#endif