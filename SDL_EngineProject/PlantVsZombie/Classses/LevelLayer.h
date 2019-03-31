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
/*�ؿ���Ƭ����*/
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
	ActiveTime m_curActiveTime;//��ǰ��ʱ��
public:
	LevelLayer();
	~LevelLayer();
	static LevelLayer*create(const string&sLevel);
	bool initWithLevel(const string&sLevel);

	void update(float dt);
	TMXTiledMap* getTiledMap()const;
	TMXLayer*getEntityLayer();
	Terrain*getClickedTerrain(const Point&nodePos);
	//��ȡ������Ӧ������
	vector<Terrain*>& getTerrainsOfRow(int row);
	//����ί��
	void setDelegate(LevelLayerDelegate*pDelegate);
	//��ȡ��ʼ̫����
	int getInitialSun()const{return m_nInitialSun;}

	Plant*getTopPlant(Carrier*carrier);
	//��ȡҪ�Ƴ����ϲ�ֲ�� ���Ȼ�ȡ�Ϲ�
	Plant*getTopPlantOfRemoval(Carrier*carrier);
	//��ȡҪ�������ϲ�ֲ��
	Plant*getTopPlantOfAttack(Carrier*carrier);
	//��ȡֲ�����ڵ�����
	Carrier*getVesselOfPlant(Carrier*carrier,Plant*plant);
	//��ȡֲ���ZOrder
	int getSumOfZOrderPlant(Terrain*terrain,Plant*plant);
	//��ȡʵ����������ж���
	ValueVector getEntityObjects();
	//��ȡ��ʬ������·��
	vector<ZombiePath*>& getZombiePaths();
	//����������ȡ��Ӧ�Ľ�ʬ��
	ZombiePath*getZombiePathOfRow(int row);
	//��ȡ��ǰ�Ĺؿ�����
	LevelCardType getLevelCardShowType()const;
	//��ȡ��ǰ�ؿ� �Ƿ��ǰ���
	ActiveTime getCurActiveTime()const;
private:
	void makeTerrainCallback(Terrain*terrain);
	void loadProperties();
	void loadZombiePath();
private:
	static bool terrainComparisonLess(Terrain* n1, Terrain* n2);
};
#endif