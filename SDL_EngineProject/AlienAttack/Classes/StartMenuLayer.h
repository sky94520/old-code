#ifndef __StartMenuLayer_H__
#define __StartMenuLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace SDL::ui;
class StartMenuLayerDelegate
{
public:
	virtual ~StartMenuLayerDelegate(){}
	virtual void gameStart()=0;
	virtual void gotoShop()=0;
	virtual void gameExit()=0;
};
/*显示开始菜单*/
class StartMenuLayer:public Layer
{
private:
	StartMenuLayerDelegate*m_pDelegate;
public:
	StartMenuLayer();
	~StartMenuLayer();
	CREATE_FUNC(StartMenuLayer);
	bool init();
	void setDelegate(StartMenuLayerDelegate*pDelegate);
private:
	void gameStart(Object*sender);
	void gotoShop(Object*sender);
	void gameExit(Object*sender);
};
#endif