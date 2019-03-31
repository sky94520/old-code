#ifndef __GameScene_H__
#define __GameScene_H__
#include "SDL_Engine/SDL_Engine.h"
#include "TouchLayer.h"
#include "PlantLayer.h"
#include "BackgroundLayer.h"
#include "SeedLayer.h"
#include "PanelLayer.h"
#include "SunshineLayer.h"
#include "Sunshine.h"
#include "ZombieLayer.h"
#include "BulletLayer.h"
using namespace SDL;
class GameScene:public Scene
	,public PlantLayerDelegate,public TouchLayerDelegate
{
private:
	TouchLayer*m_pTouchLayer;//´¥Ãþ²ã
	BackgroundLayer*m_pBackgroundLayer;//±³¾°²ã
	SeedLayer*m_pSeedLayer;//ÖÖ×Ó²ã
	PanelLayer*m_pPanelLayer;//Ãæ°å²ã
	SunshineLayer*m_pSunshineLayer;//Ì«Ñô²ã
	BulletLayer*m_pBulletLayer;
	PlantLayer*m_pPlantLayer;//Ö²Îï²ã
	ZombieLayer*m_pZombieLayer;//½©Ê¬²ã
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();

	virtual void update(float dt);
private:
	void move(const Point&pos);
	void handleCollisionAndUpdate(float dt);
private:
	virtual void shootTo(const Point&startPos,const Point&endPos,const std::string&bulletName,BulletRoute routeType);
	virtual void produceSunshine(const Point&startPos,SunshineType type,SunshineRoute route);

	virtual bool clickSunshine(const Point&pos);
	virtual bool clickSeed(const Point&pos);
	virtual bool clickShovel(const Point&pos);
	virtual void clickGround(const Point&pos);

	virtual Vector<Zombie*>* getZombies(int line=0)const
	{
		return m_pZombieLayer->getZombies(line);
	}
};
#endif