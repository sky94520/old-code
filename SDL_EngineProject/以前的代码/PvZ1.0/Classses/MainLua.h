#ifndef __MainLua_H__
#define __MainLua_H__
#include<string>
#include<cmath>
#include "SDL_Engine/SDL_Engine.h"
#include "lua/lua.h"
using namespace SDL;
/*只是保存了对lua_State的引用,一个程序只有一个*/
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
	//加载文件并且执行
	bool dofile(const std::string&filename);
	//从表中获取相应的属性(暂时这么称呼)
	const char* getStringFromTable(const std::string&tableName,const std::string&key);
	int getIntegerFromTable(const std::string&tableName,const std::string&key);
	double getDoubleFromTable(const std::string&tableName,const std::string&key);
	bool getBoolFromTable(const std::string&tableName,const std::string&key);
};
#endif