#ifndef __TouchLayer_H__
#define __TouchLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;

class TouchLayerDelegate
{
public:
	~TouchLayerDelegate(){}
	virtual void onKeyPressed(SDL_Keycode,SDL_Event*)=0;
	virtual void onKeyReleased(SDL_Keycode,SDL_Event*)=0;
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

	virtual void onKeyPressed(SDL_Keycode,SDL_Event*);
	virtual void onKeyReleased(SDL_Keycode,SDL_Event*);
};
#endif