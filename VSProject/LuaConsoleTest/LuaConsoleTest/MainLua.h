#ifndef __MainLua_H__
#define __MainLua_H__
#include<string>
#include<cmath>
#include "lua/lua.h"
/*只是保存了对lua_State的引用,一个程序只有一个*/
class MainLua
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
	//从表中获取相应的属性(暂时这么称呼)
	const char* getStringFromTable(const char*tableName,const char*key);
	int getIntegerFromTable(const char*tableName,const char*key);
};
#endif