#ifndef __GameScene_H__
#define __GameScene_H__
#include "SDL_Engine/SDL_Engine.h"
#include "BackgroundLayer.h"
#include "PanelLayer.h"
#include "MenuLayer.h"
#include "FishLayer.h"
#include "CannonLayer.h"
#include "TouchLayer.h"
#include "ChooseBulletLayer.h"
#include "sundry.h"
using namespace SDL;
class GameScene:public Scene,public PanelLayerDelegate,public MenuLayerDelegate,public TouchLayerDelegate,public ChooseBulletDelegate
{
private:
	Layer*m_pBackgroundLayer;
	PanelLayer*m_pPanelLayer;
	MenuLayer*m_pMenuLayer;
	CannonLayer*m_pCannonLayer;
	FishLayer*m_pFishLayer;
	TouchLayer*m_pTouchLayer;
	ChooseBulletLayer*m_pChooseBulletLayer;
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
public:
	virtual void update(float dt);
private://override
	virtual void pause();
	virtual void resume();
	virtual void cannonAimAt(const Point&target);
	virtual void cannonShootTo(const Point&target);
	virtual void chooseBullet(const Point&pos);
	virtual void setBulletType(BulletType type);
private:
	void checkOutCollision();
	bool checkOutCollisionBetweenFishesAndBullet();
	void checkOutCollisionBetwwenFishesAndFishingNet();
};
#endif