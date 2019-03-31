#ifndef __EventLayer_H__
#define __EventLayer_H__
#include "SDL_Engine/SDL_Engine.h"

using namespace SDL;
class EventLayerDelegate
{
public:
	virtual ~EventLayerDelegate(){}
	virtual void onKeyPressed(SDL_Keycode keyCode,SDL_Event*event)=0;
};
class EventLayer:public Layer
{
private:
	EventLayerDelegate*m_pDelegate;
	bool m_bActive;
	float m_elpased;
public:
	EventLayer();
	~EventLayer();
	CREATE_FUNC(EventLayer);
	bool init();
	void setDelegate(EventLayerDelegate*pDelegate);
	virtual void update(float dt);
private:
	void onKeyPressed(SDL_Keycode keyCode,SDL_Event*event);
	bool onTouchBegan(Touch*,SDL_Event*event);
	void onTouchMoved(Touch*,SDL_Event*event);
	void onTouchEnded(Touch*,SDL_Event*event);
};
#endif
