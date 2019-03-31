#ifndef __TouchLayer_H__
#define __TouchLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
/*�����࣬��״̬���ݸ�GameScene*/
class TouchLayerDelegate
{
public:
	virtual ~TouchLayerDelegate(){}
	virtual bool clickSeed(const Point&pos)=0;//�Ƿ������Ӱ�
	virtual bool clickShovel(const Point&pos)=0;//�Ƿ����˲���
	virtual bool clickSunshine(const Point&pos)=0;//�Ƿ�����̫��
	virtual void clickGround(const Point&pos)=0;//��������¼�
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