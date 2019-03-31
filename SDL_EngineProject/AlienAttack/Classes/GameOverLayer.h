#ifndef __GameOverLayer_H__
#define __GameOverLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class GameOverDelegate
{
public:
	virtual ~GameOverDelegate(){}
	virtual void gameRestart()=0;
};
class GameOverLayer:public Layer
{
private:
	GameOverDelegate*m_pDelegate;
public:
	GameOverLayer();
	~GameOverLayer();
	CREATE_FUNC(GameOverLayer);
	bool init();

	void setDelegate(GameOverDelegate*pDelegate);
private:
	void gameRestart(Object*sender);
};
#endif