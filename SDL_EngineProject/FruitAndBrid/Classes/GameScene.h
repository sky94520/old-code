#ifndef __GameScene_H__
#define __GameScene_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class BackgroundLayer;
class BirdLayer;
class ColumnLayer;

class GameScene:public Scene
{
private:
	BackgroundLayer*m_pBackgroundLayer;
	BirdLayer*m_pBirdLayer;
	ColumnLayer*m_pColumnLayer;
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
public:
	virtual void update(float dt);
private:
	void handleEvent(SDL_Keycode,SDL_Event*);
	bool onTouchBegan(Touch*touch,SDL_Event*);
	//´¦ÀíÅö×²
	void handleCollision();
};
#endif