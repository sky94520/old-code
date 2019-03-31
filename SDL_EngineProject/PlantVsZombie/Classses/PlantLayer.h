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
	//���ƶ���ֲ�� ��Ҫ����ֲ��Ӣ�� �Ȼ�ʬ
	vector<Character*> m_movablePlants;
	PlantLayerDelegate*m_pDelegate;
public:
	PlantLayer();
	~PlantLayer();
	CREATE_FUNC(PlantLayer);
	bool init();
	virtual void update(float dt);

	Plant*makePlant(const string&name);
	//��ֲ����������Ƴ�
	bool removePlant(Plant*plant);
	//���Ŀ�굽���ƶ�ֲ����
	void addItemToMovablePlants(Character*character);
	//��ȡ�ƶ�ֲ��
	vector<Character*>& getMovablePlantList();

	void setDelegate(PlantLayerDelegate*pDelegate);
	//�Ƿ��Ǹ߼��
	static bool isTallNut(Plant*plant);
	//��ǰֲ���Ƿ����
	static bool isActiveTimeForPlant(Plant*plant,ActiveTime activeTime);
private:
	Plant*createPlant(const string&name);
	void updateMovealbePlants(Character*character,float dt);
	void zombieUpdate(ZombieBase*zombie,float dt);
};
#endif