#ifndef __StaticData_H__
#define __StaticData_H__
#include <string>
#include <vector>
#include <functional>
#include "SDL_Engine/SDL_Engine.h"

using namespace std;
USING_NS_SDL;
//定义一些常用的宏
#define STATIC_DATA_PATH "data/static_data.plist"
/*简化使用*/
#define STATIC_DATA_STRING(key) (StaticData::getInstance()->getValueForKey(key)->asString())
#define STATIC_DATA_INT(key) (StaticData::getInstance()->getValueForKey(key)->asInt())
#define STATIC_DATA_FLOAT(key) (StaticData::getInstance()->getValueForKey(key)->asFloat())
#define STATIC_DATA_BOOLEAN(key) (StaticData::getInstance()->getValueForKey(key)->asBool())
#define STATIC_DATA_POINT(key) (StaticData::getInstance()->getPointForKey(key))
#define STATIC_DATA_SIZE(key) (StaticData::getInstance()->getSizeForKey(key))
#define STATIC_DATA_ARRAY(key) (StaticData::getInstance()->getValueForKey(key)->asValueVector())
#define STATIC_DATA_TOSTRING(key) (StaticData::getInstance()->toString(key))

/*方向,跟贴图有关*/
enum class Direction
{
	Unknown = 0,
	Down,
	Left,
	Right,
	Up,
};

class StaticData : public Object
{
private:
	static StaticData* s_pInstance;
public:
	static StaticData* getInstance();
	static void purge();
private:
	//键值对
	ValueMap m_valueMap;
	//角色键值对
	ValueMap m_characterMap;
private:
	StaticData();
	~StaticData();
	bool init();
public:
	/**
	@brief 根据键获取值
	@key 要查询的键
	@return 返回的值，如果不存在对应的值，则返回空Value
	*/
	Value* getValueForKey(const string& key);
	Point getPointForKey(const string& key);
	Size getSizeForKey(const string& key);
};
#endif