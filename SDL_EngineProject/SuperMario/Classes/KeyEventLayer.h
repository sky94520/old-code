#ifndef __KeyEventLayer_H__
#define __KeyEventLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
//发送给PlayerLayer的各种事件类型
enum EventType
{
	kEventType_None,
	kEventType_Up,
	kEventType_Down,
	kEventType_Left,
	kEventType_Right,
	kEventType_Jump,
	kEventType_Shoot,
};
class EventLayerDelegate
{
public:
	virtual ~EventLayerDelegate(){}
	virtual void keyPressed(EventType eventType)=0;
	virtual void keyReleased(EventType eventType)=0;
};
class KeyEventLayer:public Layer
{
private:
	EventLayerDelegate*m_pDelegate;
public:
	KeyEventLayer();
	~KeyEventLayer();
	CREATE_FUNC(KeyEventLayer);
	bool init();

	void setDelegate(EventLayerDelegate*pDelegate);
private:
	void onKeyPressed(SDL_Keycode keycode);
	void onKeyReleased(SDL_Keycode keycode);
};
#endif