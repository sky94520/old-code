#ifndef __GameScene_H__
#define __GameScene_H__
#include "SDL_Engine/SDL_Engine.h"
#include "BrickLayer.h"
#include "EventLayer.h"
#include "MapLayer.h"
#include "GameOverLayer.h"

using namespace SDL;
class Brick;
class PanelLayer;

class GameScene:public Scene
	,public BrickLayerDelegate,public EventLayerDelegate,public GameOverLayerDelegate
{
private:
	EventLayer*m_pEventLayer;
	MapLayer*m_pMapLayer;
	BrickLayer*m_pBrickLayer;
	PanelLayer*m_pPanelLayer;
	GameOverLayer*m_pGameOverLayer;
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
	virtual void update(float dt);
	void gameOver();
	void gameRetry();
	void gamePause();
	void gameResume();
private:
	virtual Rect getClientRect()const;
	virtual bool isCollided(Brick*brick);
	virtual void insertBrick(Brick*brick);
	virtual int clearUpLineNum();
	virtual void onKeyPressed(SDL_Keycode keyCode,SDL_Event*event);
	virtual CollideResult isGameOver(Brick*pBrick);
};
#endif