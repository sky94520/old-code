#ifndef __KeyboardLayer_H__
#define __KeyboardLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
/*电脑键盘事件，负责接受按键并发送事件*/
class EventDelegate
{
public:
	virtual ~EventDelegate(){}
	virtual void playerMove(const Point&velocity)=0;
	virtual  void playerWantShooting()=0;
};
class KeyboardLayer:public Layer
{
private:
	EventDelegate*m_pDelegate;
	Point m_velocity;//内部维护一个速度来进行速度更新
public:
	KeyboardLayer();
	~KeyboardLayer();
	CREATE_FUNC(KeyboardLayer);
	bool init();

	virtual void onKeyPressed(SDL_Keycode keycode,SDL_Event*event);
	virtual void onKeyReleased(SDL_Keycode keycode,SDL_Event*event);
	void onEvent(const Uint8*keyStates,SDL_Event*event);

	void setDelegate(EventDelegate*pDelegate);
};
#endif