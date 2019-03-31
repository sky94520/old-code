#ifndef __GameOverLayer_H__
#define __GameOverLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class GameOverLayerDelegate
{
public:
	virtual ~GameOverLayerDelegate(){}
	virtual void gameRetry()=0;
};
class GameOverLayer:public Layer
{
private:
	GameOverLayerDelegate*m_pDelegate;
	Menu*m_pMenu;
public:
	GameOverLayer();
	~GameOverLayer();
	CREATE_FUNC(GameOverLayer);
	bool init();
	void setDelegate(GameOverLayerDelegate*pDelegate);
	void show();
	void hide();
private:
	void gameRetry(Object*sender);
};
#endif