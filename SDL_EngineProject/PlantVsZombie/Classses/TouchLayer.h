#ifndef __TouchLayer_H__
#define __TouchLayer_H__

#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;

enum class GameState;

class TouchLayerDelegate
{
public:
	virtual ~TouchLayerDelegate(){}
	virtual GameState getGameState()const = 0;
	virtual bool touchBeganOfPlayState(Touch*,SDL_Event*) = 0;
	virtual void touchMovedOfPlayState(Touch*touch,SDL_Event*event) = 0;
	virtual void touchEndedOfPlayState(Touch*touch,SDL_Event*event) = 0;

	virtual bool touchBeganOfCardChooseState(Touch*touch,SDL_Event*event) = 0;
	virtual void touchMovedOfCardChooseState(Touch*touch,SDL_Event*evnet) = 0;
	virtual void touchEndedOfCardChooseState(Touch*touch,SDL_Event*evnet) = 0;
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
	void setDelegate(TouchLayerDelegate* Delegate);
public:
	virtual bool onTouchBegan(Touch*,SDL_Event*);
	virtual void onTouchMoved(Touch*touch,SDL_Event*event);
	virtual void onTouchEnded(Touch*touch,SDL_Event*event);
};
#endif