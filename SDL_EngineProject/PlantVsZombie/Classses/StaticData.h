#ifndef __StaticData_H__
#define __StaticData_H__
#include<map>
#include<string>
#include<vector>
#include<cctype>
#include<sstream>
#include<algorithm>

#include "SDL_Engine/SDL_Engine.h"
#include "Terrain.h"

using namespace std;
using namespace SDL;

enum class PlantType;
enum class Direction;

#define STATIC_DATA_PATH "data/static_data.plist"
/*简化使用*/
#define STATIC_DATA_STRING(key) (StaticData::getInstance()->getValueForKey(key)->asString())
#define STATIC_DATA_INT(key) (StaticData::getInstance()->getValueForKey(key)->asInt())
#define STATIC_DATA_FLOAT(key) (StaticData::getInstance()->getValueForKey(key)->asFloat())
#define STATIC_DATA_BOOLEAN(key) (StaticData::getInstance()->getValueForKey(key)->asBool())
#define STATIC_DATA_POINT(key) (StaticData::getInstance()->getPointForKey(key))
/*实体活动时间*/
enum class ActiveTime
{
	All,
	Day,
	Night,
};
typedef struct _CardStruct
{
	string desc;
	int worth;
	float cd;
	float readyTime;
	ActiveTime active;
	vector<TerrainType> terrains;
	string necessoryItem;
}CardStruct;
/*僵尸数据结构体*/
typedef struct ZombieCsvStruct
{
	int hp;
	float speed;
	string garnishry;
	Rect rect;
}ZombieCsvStruct;
/*植物数据结构体*/
typedef struct PlantCsvStruct
{
	int hp;
	float cd;
	PlantType type;
	Direction dir;
}PlantCsvStruct;
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
	//保存着卡片对应的数据
	map<string,CardStruct>m_cardStructMap;
	//保存着僵尸的数据
	map<string,ZombieCsvStruct> m_zombieCsvMap;
	//保存着植物的数据
	map<string,PlantCsvStruct> m_plantCsvMap;
public:
	static StaticData*getInstance();
	static void purge();
	bool init();

	/**
	@brief 根据键获取值
	@key 要查询的键
	@return 返回的值，如果不存在对应的值，则返回空Value
	*/
	Value *getValueForKey(const string&key);
	/**
	@brief 根据键获取对应的Point
	@key 要查询的键
	@return 返回Point 如果不存在或者不合法。。。返回什么比较好？ 目前(0,0)
	*/
	Point getPointForKey(const string&key);
	//转换字符串成TerrainType
	static TerrainType convertStrToTerrainType(const string&sType);
	static ActiveTime convertStrToActiveType(const string&sType);
	static PlantType convertStrToPlantType(const string& sType);
	static Direction convertStrToDir(const string&sType);
	//转化成小写字符
	static string toLowerCase(const string&text);
	CardStruct* getCardStruct(const string&name);
	//获取对应的僵尸结构体
	ZombieCsvStruct* getZombieStructForName(const string&zombieName);
	//获取对应的植物结构体
	PlantCsvStruct* getPlantCsvStructForName(const string& plantName);
private:
	void parseCard();
	void parseZombieCsvData();
	void parsePlantCsvData();
};
#endif