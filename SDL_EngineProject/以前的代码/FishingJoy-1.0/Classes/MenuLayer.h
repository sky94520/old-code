#ifndef __MenuLayer_H__
#define __MenuLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class MenuLayerDelegate
{
public:
	virtual ~MenuLayerDelegate(){}
	virtual void resume()=0;
};
class MenuLayer:public Layer
{
private:
	MenuLayerDelegate*m_pDelegate;
public:
	MenuLayer();
	~MenuLayer();
	CREATE_FUNC(MenuLayer);
	bool init();
public:
	void setDelegate(MenuLayerDelegate*pDelegate);
private:
	void continueCallback(Object*obj);
	void exitCallback(Object*obj);
};
#endif