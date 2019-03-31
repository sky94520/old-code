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
/*��ʹ��*/
#define STATIC_DATA_STRING(key) (StaticData::getInstance()->getValueForKey(key)->asString())
#define STATIC_DATA_INT(key) (StaticData::getInstance()->getValueForKey(key)->asInt())
#define STATIC_DATA_FLOAT(key) (StaticData::getInstance()->getValueForKey(key)->asFloat())
#define STATIC_DATA_BOOLEAN(key) (StaticData::getInstance()->getValueForKey(key)->asBool())
#define STATIC_DATA_POINT(key) (StaticData::getInstance()->getPointForKey(key))
/*ʵ��ʱ��*/
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
/*��ʬ���ݽṹ��*/
typedef struct ZombieCsvStruct
{
	int hp;
	float speed;
	string garnishry;
	Rect rect;
}ZombieCsvStruct;
/*ֲ�����ݽṹ��*/
typedef struct PlantCsvStruct
{
	int hp;
	float cd;
	PlantType type;
	Direction dir;
}PlantCsvStruct;
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
	//�����ſ�Ƭ��Ӧ������
	map<string,CardStruct>m_cardStructMap;
	//�����Ž�ʬ������
	map<string,ZombieCsvStruct> m_zombieCsvMap;
	//������ֲ�������
	map<string,PlantCsvStruct> m_plantCsvMap;
public:
	static StaticData*getInstance();
	static void purge();
	bool init();

	/**
	@brief ���ݼ���ȡֵ
	@key Ҫ��ѯ�ļ�
	@return ���ص�ֵ����������ڶ�Ӧ��ֵ���򷵻ؿ�Value
	*/
	Value *getValueForKey(const string&key);
	/**
	@brief ���ݼ���ȡ��Ӧ��Point
	@key Ҫ��ѯ�ļ�
	@return ����Point ��������ڻ��߲��Ϸ�����������ʲô�ȽϺã� Ŀǰ(0,0)
	*/
	Point getPointForKey(const string&key);
	//ת���ַ�����TerrainType
	static TerrainType convertStrToTerrainType(const string&sType);
	static ActiveTime convertStrToActiveType(const string&sType);
	static PlantType convertStrToPlantType(const string& sType);
	static Direction convertStrToDir(const string&sType);
	//ת����Сд�ַ�
	static string toLowerCase(const string&text);
	CardStruct* getCardStruct(const string&name);
	//��ȡ��Ӧ�Ľ�ʬ�ṹ��
	ZombieCsvStruct* getZombieStructForName(const string&zombieName);
	//��ȡ��Ӧ��ֲ��ṹ��
	PlantCsvStruct* getPlantCsvStructForName(const string& plantName);
private:
	void parseCard();
	void parseZombieCsvData();
	void parsePlantCsvData();
};
#endif