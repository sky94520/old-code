#ifndef __StaticData_H__
#define __StaticData_H__
#include <string>
#include <vector>
#include <functional>
#include "SDL_Engine/SDL_Engine.h"

using namespace std;
USING_NS_SDL;
//����һЩ���õĺ�
#define STATIC_DATA_PATH "data/static_data.plist"
/*��ʹ��*/
#define STATIC_DATA_STRING(key) (StaticData::getInstance()->getValueForKey(key)->asString())
#define STATIC_DATA_INT(key) (StaticData::getInstance()->getValueForKey(key)->asInt())
#define STATIC_DATA_FLOAT(key) (StaticData::getInstance()->getValueForKey(key)->asFloat())
#define STATIC_DATA_BOOLEAN(key) (StaticData::getInstance()->getValueForKey(key)->asBool())
#define STATIC_DATA_POINT(key) (StaticData::getInstance()->getPointForKey(key))
#define STATIC_DATA_SIZE(key) (StaticData::getInstance()->getSizeForKey(key))
#define STATIC_DATA_ARRAY(key) (StaticData::getInstance()->getValueForKey(key)->asValueVector())
#define STATIC_DATA_TOSTRING(key) (StaticData::getInstance()->toString(key))

/*����,����ͼ�й�*/
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
	//��ֵ��
	ValueMap m_valueMap;
	//��ɫ��ֵ��
	ValueMap m_characterMap;
private:
	StaticData();
	~StaticData();
	bool init();
public:
	/**
	@brief ���ݼ���ȡֵ
	@key Ҫ��ѯ�ļ�
	@return ���ص�ֵ����������ڶ�Ӧ��ֵ���򷵻ؿ�Value
	*/
	Value* getValueForKey(const string& key);
	Point getPointForKey(const string& key);
	Size getSizeForKey(const string& key);
};
#endif