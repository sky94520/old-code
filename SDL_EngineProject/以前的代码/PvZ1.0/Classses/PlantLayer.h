#ifndef __PlantLayer_H__
#define __PlantLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "SunshineLayer.h"
#include "Sunshine.h"
#include "BulletLayer.h"

using namespace std;
using namespace SDL;
class Plant;
class Zombie;
class PlantLayerDelegate
{
public:
	virtual ~PlantLayerDelegate(){}
	//发射子弹
	virtual void shootTo(const Point&startPos,const Point&endPos,const std::string&bulletName,BulletRoute routeType)=0;
	//生产太阳
	virtual void produceSunshine(const Point&startPos,SunshineType type,SunshineRoute route)=0;
	virtual Vector<Zombie*>* getZombies(int line = 0)const = 0;
};
class PlantLayer:public Layer
{
private:
	Vector<Plant*> m_plants;//植物集合
	PlantLayerDelegate*m_pDelegate;
public:
	PlantLayer();
	~PlantLayer();
	CREATE_FUNC(PlantLayer);
	bool init();

	virtual void update(float dt);
	void bindPlant(Plant*plant);
	void deletePlant(Plant*plant);
	void setDelegate(PlantLayerDelegate*pDelegate);
private:
	void lineShootTo(Plant*plant);//豌豆射手类 发动技能
	void sunshine(Plant*plant);//太阳光
	void bomb(Plant*plant);//炸弹
	//樱桃炸弹
	void cherryBomb(Plant*plant);
	//土豆雷
	void potatoMine(Plant*plant);
};
#endif