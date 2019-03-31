#ifndef __StaticData_H__
#define __StaticData_H__
#include<string>
#include<vector>

#include "SDL_Engine/SDL_Engine.h"

using namespace std;
using namespace SDL;

#define STATIC_DATA_PATH "data/static_data.plist"
/*简化使用*/
#define STATIC_DATA_STRING(key) (StaticData::getInstance()->getValueForKey(key)->asString())
#define STATIC_DATA_INT(key) (StaticData::getInstance()->getValueForKey(key)->asInt())
#define STATIC_DATA_FLOAT(key) (StaticData::getInstance()->getValueForKey(key)->asFloat())
#define STATIC_DATA_BOOLEAN(key) (StaticData::getInstance()->getValueForKey(key)->asBool())
#define STATIC_DATA_POINT(key) (StaticData::getInstance()->getPointForKey(key))
#define STATIC_DATA_ARRAY(key) (StaticData::getInstance()->getValueForKey(key)->asValueVector())
#define STATIC_DATA_TOSTRING(key) (StaticData::getInstance()->toString(key))
//定义宏来方便设置键值
#define LUA_ENUM(L,literal,number)\
	lua_pushstring(L,literal);\
	lua_pushnumber(L,number);\
	lua_settable(L,-3)

/*方向,跟贴图有关*/
enum class Direction
{
	Down,
	Left,
	Right,
	Up,
};
/*单实例对象 保存着游戏的静态数据*/
class StaticData:public Object
{
	SDL_SYNTHESIZE_READONLY(string,m_staticDataPath,StaticDataPath);//获取静态数据类型
private:
	StaticData();
	~StaticData();
private:
	static StaticData* m_pInstance;
	//保存数据字典
	ValueMap m_plistMap;
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
	/*图片切割函数
	*@ 从对应图片的切割部分按照size进行切割，每换一行回调一次
	*/
	bool split(Texture* texture,Rect* cap,const Size& size,const function<void (int,const vector<SpriteFrame*>& frames)>& callback);
	//获取对应角色的方向动画名
	Animation* getAnimationOfDirection(const string& playerName,Direction dir);
};
#endif