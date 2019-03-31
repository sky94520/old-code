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
/*简化使用*/
#define STATIC_DATA_STRING(key) (StaticData::getInstance()->getValueForKey(key).asString())
#define STATIC_DATA_INT(key) StaticData::getInstance()->getValueForKey(key).asInt()
#define STATIC_DATA_FLOAT(key) StaticData::getInstance()->getValueForKey(key).asFloat()
#define STATIC_DATA_BOOLEAN(key) StaticData::getInstance()->getValueForKey(key).asBool()
#define STATIC_DATA_POINT(key) (StaticData::getInstance()->getPointForKey(key))

/*csv简化使用*/
#define STATIC_FISH_EXP(id) (StaticData::getInstance()->getExpByFishID(id))
#define STATIC_FISH_ENERGY(id) (StaticData::getInstance()->getEnergyByFishID(id))
#define STATIC_FISH_GOLD(id) (StaticData::getInstance()->getGoldByFishID(id))
#define STATIC_FISH_MAX(id) (StaticData::getInstance()->getMaxByFishID(id))
#define STATIC_FISH_MAX_PER_TIME(id) (StaticData::getInstance()->getMaxPerTimeByFishID(id))
#define STATIC_FISH_WEIGHT(id) (StaticData::getInstance()->getWeightByFishID(id))

/*鱼的相关信息结构体*/
typedef struct FishConfig
{
	int id;
	string name;
	string desc;
	int gold;
	int weight;
	int max_per_time;//每次能生成的最大数目
	int max;//场上最多出现的数目

	string speedUpName;//加速技能名字
	string scaredName;//鱼群来临技能
	string invulnerableName;//无敌技能
public:
	FishConfig()
		:id(0),gold(0),weight(0),max_per_time(0),max(0)
	{}
}FishConfig;
/*鱼的出生配置 用于鱼潮*/
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
/*宝箱奖励*/
typedef struct ChestReward
{
	string type;//类型
	int number;//数目
}ChestReward;
/*保存着鱼所对应的可能的奖品*/
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
/*单实例对象 保存着游戏的静态数据*/
class StaticData:public Object
{
	SDL_SYNTHESIZE_READONLY(string,m_staticDataPath,StaticDataPath);//获取静态数据类型
private:
	StaticData();
	~StaticData();
private:
	static StaticData*m_pInstance;
	//保存数据字典
	ValueMap m_plistMap;
	//鱼的配置信息
	vector<FishConfig*> m_fishConfigs;
	//鱼的路径信息
	ValueMap m_pathes;
	//鱼和路径对应的信息
	map<int,vector<int> > m_fishPathes;
	//鱼潮的相关信息
	map<int,FishTideConfig> m_fishTideConfigs;
	//宝箱奖励相关信息
	vector<ChestReward> m_chestRewards;
	//鱼可能掉落的物品集合
	vector<FishReward> m_fishRewardVec;
public:
	static StaticData*getInstance();
	static void purge();
	bool init();

	/**
	@brief 根据键获取值
	@key 要查询的键
	@return 返回的值，如果不存在对应的值，则返回空Value
	*/
	Value &getValueForKey(const string&key);
	/**
	@brief 根据键获取对应的Point
	@key 要查询的键
	@return 返回Point 如果不存在或者不合法。。。返回什么比较好？ 目前(0,0)
	*/
	Point getPointForKey(const string&key);
	/**获取对应的鱼潮信息 todo
	*/
	FishTideConfig& getFishTideByID(int fishTideID);
	/**根据路径id和是否反向获取动作，从右向左
	*@pathID 路径id
	*@size 鱼的实体大小
	*@offsetX x轴的偏移
	*@randomY y轴偏移
	*@reverse 是否反向
	*/
	RotateAndSpeed*getActionByPathID(int pathID,const Size&size,float offsetX,float randomY,bool reverse);
	/**获取开始位置
	*@pathID 路径的id
	*@reverse 是否反向
	*/
	Point getStartPosByPathID(int pathID,bool reverse = false);

	FishConfig*getFishConfigForID(int id)const;
	/**获取一条鱼所对应的所有路径ID
	*fishID 鱼的id
	*/
	const vector<int>* getTotalPathes(int fishID)const;
	//获取鱼所对应的经验值 分数即经验
	float getExpByFishID(int id);
	//获取鱼所对应的能量值
	float getEnergyByFishID(int id);
	//根据id获取对应的金币
	int getGoldByFishID(int id);
	//根据id获取对应的最大出场值
	int getMaxByFishID(int id);
	//获取一次能产生的最大数目
	int getMaxPerTimeByFishID(int id);
	//获取权数
	int getWeightByFishID(int id);
	//获取全部的箱子奖励物品
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