#include <iostream>
#include "lua.h"

extern void addLuaLoader(lua_State* pL, lua_CFunction func);
extern int load_test(lua_State* pL);
extern int sky(lua_State* pL);

int main()
{
	lua_State *pL = luaL_newstate();
	luaL_openlibs(pL);

	lua_register(pL, "sky", sky);
	addLuaLoader(pL, load_test);
	//加载文件
	luaL_dofile(pL,"text.lua");
	//执行协程
	int result = lua_getglobal(pL,"test");
	lua_pushinteger(pL,1);
	//开始协程
	 result = lua_resume(pL,nullptr,1);
	 int n = lua_gettop(pL);
	
	if (LUA_ERRRUN == result)
	{
		printf("%s",luaL_checkstring(pL,-1));
	}
	else if (LUA_YIELD == result)
	{
		int x1 = luaL_checkinteger(pL,1);
		int x2 = luaL_checkinteger(pL,2);

		lua_pop(pL, 2);
		lua_pushinteger(pL,2);
		lua_pushinteger(pL,3);

		int n = lua_gettop(pL);
		result = lua_resume(pL,nullptr,0);
	}

	lua_close(pL);

	getchar();

	return 0;
}

void addLuaLoader(lua_State* pL, lua_CFunction func)
{
	//空指针，直接返回
	if (func == nullptr)
		return ;
	//获取对应的表
	lua_getglobal(pL, "package");
	lua_getfield(pL, -1 ,"searchers");
	
	lua_pushcfunction(pL, func);
	//把searchers表原来的2以后的项往后移1
	for (int i = (int)lua_rawlen(pL, -2) + 1; i > 2; i--)
	{
		//获取项到栈顶
		lua_rawgeti(pL, -2, i - 1);
		//转移
		lua_rawseti(pL, -3, i);
	}
	//searchers[2] = func
	lua_rawseti(pL, -2, 2);

	lua_setfield(pL, -2, "searchers");
	//清除栈顶，即清除 package表
	lua_pop(pL, 1);
}

int load_test(lua_State* pL)
{
	auto name = luaL_checkstring(pL, 1);
	printf("load file:%s", name);
	//FILE* file = fopen(filepath, "r");

	lua_pushstring(pL, name);
	return 2;
}

int sky(lua_State* pL)
{
	auto str = luaL_checkstring(pL, 1);
	printf("the number is %s", str);

	return 0;
}