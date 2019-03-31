#ifndef __LevelLayer_H__
#define __LevelLayer_H__
#include<string>
#include<vector>
#include<algorithm>
#include "SDL_Engine/SDL_Engine.h"
#include "StaticData.h"

using namespace std;
using namespace SDL;

class LevelLayerDelegate
{
public:
	virtual ~LevelLayerDelegate(){}
	virtual void makeSun(int number,FiniteTimeAction*action,const Point&bornPos)=0;
};
typedef struct ZombiePath
{
	vector<Point> points;
	int row;
}ZombiePath;

class Terrain;
class Plant;
class Carrier;
/*关卡卡片类型*/
enum class LevelCardType
{
	Plant,
	Zombie,
};

class VesselPlant;

class LevelLayer:public Layer
{
private:
	TMXTiledMap*m_pTiledMap;
	map<int,vector<Terrain*> >m_terrains;
	LevelLayerDelegate*m_pDelegate;
	bool m_bProduceSun;
	int m_nInitialSun;
	float m_elapsed;
	LevelCardType m_levelCardType;
	vector<ZombiePath*> m_zombiePathVec;
	ActiveTime m_curActiveTime;//当前的时间
public:
	LevelLayer();
	~LevelLayer();
	static LevelLayer*create(const string&sLevel);
	bool initWithLevel(const string&sLevel);

	void update(float dt);
	TMXTiledMap* getTiledMap()const;
	TMXLayer*getEntityLayer();
	Terrain*getClickedTerrain(const Point&nodePos);
	//获取行所对应的塔基
	vector<Terrain*>& getTerrainsOfRow(int row);
	//设置委托
	void setDelegate(LevelLayerDelegate*pDelegate);
	//获取初始太阳光
	int getInitialSun()const{return m_nInitialSun;}

	Plant*getTopPlant(Carrier*carrier);
	//获取要移除的上层植物 优先获取南瓜
	Plant*getTopPlantOfRemoval(Carrier*carrier);
	//获取要攻击的上层植物
	Plant*getTopPlantOfAttack(Carrier*carrier);
	//获取植物相邻的容器
	Carrier*getVesselOfPlant(Carrier*carrier,Plant*plant);
	//获取植物的ZOrder
	int getSumOfZOrderPlant(Terrain*terrain,Plant*plant);
	//获取实体对象层的所有对象
	ValueVector getEntityObjects();
	//获取僵尸的行走路径
	vector<ZombiePath*>& getZombiePaths();
	//根据行数获取对应的僵尸行
	ZombiePath*getZombiePathOfRow(int row);
	//获取当前的关卡类型
	LevelCardType getLevelCardShowType()const;
	//获取当前关卡 是否是白天
	ActiveTime getCurActiveTime()const;
private:
	void makeTerrainCallback(Terrain*terrain);
	void loadProperties();
	void loadZombiePath();
private:
	static bool terrainComparisonLess(Terrain* n1, Terrain* n2);
};
#endif