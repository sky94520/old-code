#ifndef __MainLayer_H__
#define __MainLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
/*ÓÎÏ·Ö÷²¼¾°*/
class MainLayer:public Layer
{
private:
	Sprite*m_pBackground;
	Sprite*m_pFloor;
	Sprite*m_pTitle;
public:
	MainLayer();
	~MainLayer();

	static Scene*createScene();
	CREATE_FUNC(MainLayer);
	bool init();
public:
	virtual void update(float dt);
private:
	void menuStartGame(Object*);
	void menuGameExit(Object*);
};
#endif