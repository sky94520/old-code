#ifndef __StaticData_H__
#define __StaticData_H__
#include<map>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>

#include "SDL_Engine/SDL_Engine.h"
using namespace std;
using namespace SDL;

class RotateAndSpeed;

#define STATIC_DATA_PATH "data/static_data.plist"
/*��ʹ��*/
#define STATIC_DATA_STRING(key) (StaticData::getInstance()->getValueForKey(key).asString())
#define STATIC_DATA_INT(key) StaticData::getInstance()->getValueForKey(key).asInt()
#define STATIC_DATA_FLOAT(key) StaticData::getInstance()->getValueForKey(key).asFloat()
#define STATIC_DATA_BOOLEAN(key) StaticData::getInstance()->getValueForKey(key).asBool()
#define STATIC_DATA_POINT(key) (StaticData::getInstance()->getPointForKey(key))

/*csv��ʹ��*/
#define STATIC_FISH_EXP(id) (StaticData::getInstance()->getExpByFishID(id))
#define STATIC_FISH_ENERGY(id) (StaticData::getInstance()->getEnergyByFishID(id))
#define STATIC_FISH_GOLD(id) (StaticData::getInstance()->getGoldByFishID(id))
#define STATIC_FISH_MAX(id) (StaticData::getInstance()->getMaxByFishID(id))
#define STATIC_FISH_MAX_PER_TIME(id) (StaticData::getInstance()->getMaxPerTimeByFishID(id))
#define STATIC_FISH_WEIGHT(id) (StaticData::getInstance()->getWeightByFishID(id))

/*��������Ϣ�ṹ��*/
typedef struct FishConfig
{
	int id;
	string name;
	string desc;
	int gold;
	int weight;
	int max_per_time;//ÿ�������ɵ������Ŀ
	int max;//���������ֵ���Ŀ

	string speedUpName;//���ټ�������
	string scaredName;//��Ⱥ���ټ���
	string invulnerableName;//�޵м���
public:
	FishConfig()
		:id(0),gold(0),weight(0),max_per_time(0),max(0)
	{}
}FishConfig;
/*��ĳ������� �����㳱*/
typedef struct FishBornConfig
{
	Point pos;
	int fishID;
public:
	FishBornConfig(const Point&pos,int id)
		:pos(pos),fishID(id)
	{
	}
}FishBornConfig;

typedef struct FishTideConfig
{
	int count;
	int path_id;
	vector<FishBornConfig> fishes;
}FishTideConfig;
/*���佱��*/
typedef struct ChestReward
{
	string type;//����
	int number;//��Ŀ
}ChestReward;
/*������������Ӧ�Ŀ��ܵĽ�Ʒ*/
typedef struct FishReward
{
	int fishID;
	string type;
	int number;
	float scope;
public:
	FishReward(int fishID,const string&type,int number,float scope)
		:fishID(fishID),type(type),number(number),scope(scope)
	{
	}
}FishReward;
/*��ʵ������ ��������Ϸ�ľ�̬����*/
class StaticData:public Object
{
	SDL_SYNTHESIZE_READONLY(string,m_staticDataPath,StaticDataPath);//��ȡ��̬��������
private:
	StaticData();
	~StaticData();
private:
	static StaticData*m_pInstance;
	//���������ֵ�
	ValueMap m_plistMap;
	//���������Ϣ
	vector<FishConfig*> m_fishConfigs;
	//���·����Ϣ
	ValueMap m_pathes;
	//���·����Ӧ����Ϣ
	map<int,vector<int> > m_fishPathes;
	//�㳱�������Ϣ
	map<int,FishTideConfig> m_fishTideConfigs;
	//���佱�������Ϣ
	vector<ChestReward> m_chestRewards;
	//����ܵ������Ʒ����
	vector<FishReward> m_fishRewardVec;
public:
	static StaticData*getInstance();
	static void purge();
	bool init();

	/**
	@brief ���ݼ���ȡֵ
	@key Ҫ��ѯ�ļ�
	@return ���ص�ֵ����������ڶ�Ӧ��ֵ���򷵻ؿ�Value
	*/
	Value &getValueForKey(const string&key);
	/**
	@brief ���ݼ���ȡ��Ӧ��Point
	@key Ҫ��ѯ�ļ�
	@return ����Point ��������ڻ��߲��Ϸ�����������ʲô�ȽϺã� Ŀǰ(0,0)
	*/
	Point getPointForKey(const string&key);
	/**��ȡ��Ӧ���㳱��Ϣ todo
	*/
	FishTideConfig& getFishTideByID(int fishTideID);
	/**����·��id���Ƿ����ȡ��������������
	*@pathID ·��id
	*@size ���ʵ���С
	*@offsetX x���ƫ��
	*@randomY y��ƫ��
	*@reverse �Ƿ���
	*/
	RotateAndSpeed*getActionByPathID(int pathID,const Size&size,float offsetX,float randomY,bool reverse);
	/**��ȡ��ʼλ��
	*@pathID ·����id
	*@reverse �Ƿ���
	*/
	Point getStartPosByPathID(int pathID,bool reverse = false);

	FishConfig*getFishConfigForID(int id)const;
	/**��ȡһ��������Ӧ������·��ID
	*fishID ���id
	*/
	const vector<int>* getTotalPathes(int fishID)const;
	//��ȡ������Ӧ�ľ���ֵ ����������
	float getExpByFishID(int id);
	//��ȡ������Ӧ������ֵ
	float getEnergyByFishID(int id);
	//����id��ȡ��Ӧ�Ľ��
	int getGoldByFishID(int id);
	//����id��ȡ��Ӧ��������ֵ
	int getMaxByFishID(int id);
	//��ȡһ���ܲ����������Ŀ
	int getMaxPerTimeByFishID(int id);
	//��ȡȨ��
	int getWeightByFishID(int id);
	//��ȡȫ�������ӽ�����Ʒ
	vector<ChestReward>&getChestRewards();
	vector<FishReward>&getFishRewards();
private:
	ActionInterval*getAction(const ValueMap&valueMap,const Size&size,float offsetX,float randomY,bool reverse);
	
	void parseFishConfig();
	void parseFishPath();
	void parseFishTide();
	void parseChestReward();
	void parseFishReward();
};
#endif