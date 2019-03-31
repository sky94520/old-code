#ifndef __PlantLayer_H__
#define __PlantLayer_H__
#include<vector>
#include<string>
#include<algorithm>
#include "SDL_Engine/SDL_Engine.h"
#include "StaticData.h"

using namespace std;
using namespace SDL;
class Plant;
class SunFlower;
class PlantFactory;
class NightPlant;
class ZombieBase;
class Character;

class PlantLayerDelegate
{
public:
	virtual ~PlantLayerDelegate(){}
	virtual ActiveTime getCurActiveTime()const=0;
	virtual ZombieBase*findFirstCollidedZombie(int row,const Rect&rect) = 0;
};

class PlantLayer:public Layer
{
private:
	PlantFactory*m_pPlantFactory;
	vector<Plant*> m_plants;
	//会移动的植物 主要包括植物英雄 魅惑僵尸
	vector<Character*> m_movablePlants;
	PlantLayerDelegate*m_pDelegate;
public:
	PlantLayer();
	~PlantLayer();
	CREATE_FUNC(PlantLayer);
	bool init();
	virtual void update(float dt);

	Plant*makePlant(const string&name);
	//把植物从容器中移除
	bool removePlant(Plant*plant);
	//添加目标到可移动植物内
	void addItemToMovablePlants(Character*character);
	//获取移动植物
	vector<Character*>& getMovablePlantList();

	void setDelegate(PlantLayerDelegate*pDelegate);
	//是否是高坚果
	static bool isTallNut(Plant*plant);
	//当前植物是否积极
	static bool isActiveTimeForPlant(Plant*plant,ActiveTime activeTime);
private:
	Plant*createPlant(const string&name);
	void updateMovealbePlants(Character*character,float dt);
	void zombieUpdate(ZombieBase*zombie,float dt);
};
#endif