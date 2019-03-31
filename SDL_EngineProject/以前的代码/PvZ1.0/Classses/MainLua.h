#ifndef __MainLua_H__
#define __MainLua_H__
#include<string>
#include<cmath>
#include "SDL_Engine/SDL_Engine.h"
#include "lua/lua.h"
using namespace SDL;
/*ֻ�Ǳ����˶�lua_State������,һ������ֻ��һ��*/
class MainLua:public Object
{
private:
	lua_State*m_pScriptContext;
	static MainLua*m_pInstance;
	MainLua();
	~MainLua();
public:
	static MainLua*getInstance();
	void purge();
	lua_State*getLuaState()const;
	//�����ļ�����ִ��
	bool dofile(const std::string&filename);
	//�ӱ��л�ȡ��Ӧ������(��ʱ��ô�ƺ�)
	const char* getStringFromTable(const std::string&tableName,const std::string&key);
	int getIntegerFromTable(const std::string&tableName,const std::string&key);
	double getDoubleFromTable(const std::string&tableName,const std::string&key);
	bool getBoolFromTable(const std::string&tableName,const std::string&key);
};
#endif