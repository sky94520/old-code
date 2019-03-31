#ifndef __StaticData_H__
#define __StaticData_H__
#include<string>
#include<vector>

#include "SDL_Engine/SDL_Engine.h"

using namespace std;
using namespace SDL;

#define STATIC_DATA_PATH "data/static_data.plist"
/*��ʹ��*/
#define STATIC_DATA_STRING(key) (StaticData::getInstance()->getValueForKey(key)->asString())
#define STATIC_DATA_INT(key) (StaticData::getInstance()->getValueForKey(key)->asInt())
#define STATIC_DATA_FLOAT(key) (StaticData::getInstance()->getValueForKey(key)->asFloat())
#define STATIC_DATA_BOOLEAN(key) (StaticData::getInstance()->getValueForKey(key)->asBool())
#define STATIC_DATA_POINT(key) (StaticData::getInstance()->getPointForKey(key))
#define STATIC_DATA_ARRAY(key) (StaticData::getInstance()->getValueForKey(key)->asValueVector())
#define STATIC_DATA_TOSTRING(key) (StaticData::getInstance()->toString(key))
//��������������ü�ֵ
#define LUA_ENUM(L,literal,number)\
	lua_pushstring(L,literal);\
	lua_pushnumber(L,number);\
	lua_settable(L,-3)

/*����,����ͼ�й�*/
enum class Direction
{
	Down,
	Left,
	Right,
	Up,
};
/*��ʵ������ ��������Ϸ�ľ�̬����*/
class StaticData:public Object
{
	SDL_SYNTHESIZE_READONLY(string,m_staticDataPath,StaticDataPath);//��ȡ��̬��������
private:
	StaticData();
	~StaticData();
private:
	static StaticData* m_pInstance;
	//���������ֵ�
	ValueMap m_plistMap;
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
	/*ͼƬ�и��
	*@ �Ӷ�ӦͼƬ���и�ְ���size�����иÿ��һ�лص�һ��
	*/
	bool split(Texture* texture,Rect* cap,const Size& size,const function<void (int,const vector<SpriteFrame*>& frames)>& callback);
	//��ȡ��Ӧ��ɫ�ķ��򶯻���
	Animation* getAnimationOfDirection(const string& playerName,Direction dir);
};
#endif