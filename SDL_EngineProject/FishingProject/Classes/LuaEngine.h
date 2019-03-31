#ifndef __LuaEngine_H__
#define __LuaEngine_H__
#include<string>
#include<cmath>
#include "SDL_Engine/SDL_Engine.h"
#include "lua/lua.h"
using namespace SDL;

/*只是保存了对lua_State的引用,一个程序只有一个*/
class LuaEngine:public Object
{
private:
	lua_State*m_pScriptContext;
	static LuaEngine*m_pInstance;
	LuaEngine();
	~LuaEngine();
public:
	static LuaEngine*getInstance();
	void purge();
	lua_State*getLuaState()const;
	//加载脚本并执行
	int dofile(const std::string&fn);
	//从表中获取相应的属性(暂时这么称呼)
	const char* getStringFromTable(const char*tableName,const char*key);
	int getIntegerFromTable(const char*tableName,const char*key);
	float getFloatFromTable(const char*tableName,const char*key);
};
#endif