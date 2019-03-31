#include "lua.h"

static int ll_require (lua_State *L)
{
  //获取对应的名称
  const char *name = luaL_checkstring(L, 1);
  //如果已经加载过了，则不再加载
  lua_settop(L, 1);  
  lua_getfield(L, LUA_REGISTRYINDEX, "_LOADED");
  lua_getfield(L, 2, name);  
  if (lua_toboolean(L, -1))  
    return 1;  
  //从栈中弹出lua_getfile()的结果
  lua_pop(L, 1);
  //发现加载器，若发现成功，栈中应该存在模块(类型为function)和字符串
  findloader(L, name);
  //压入必要的参数入栈
  lua_pushstring(L, name);  
  lua_insert(L, -2);  
  //运行加载器来加载模块
  lua_call(L, 2, 1);  
  /* _LOADED[name] = returned value */
  if (!lua_isnil(L, -1))  
    lua_setfield(L, 2, name);
  //没有返回值则让 _LOADED[name] = true
  if (lua_getfield(L, 2, name) == LUA_TNIL) 
  {   
    lua_pushboolean(L, 1);  
    lua_pushvalue(L, -1);  
    lua_setfield(L, 2, name);  
  }
  return 1;
}

static void findloader (lua_State *L, const char *name) {
  int i;
  luaL_Buffer msg;
  //仅初始化该结构体
  luaL_buffinit(L, &msg);
  /* 把 'package.searchers' 放到索引为3的栈中 */
  if (lua_getfield(L, lua_upvalueindex(1), "searchers") != LUA_TTABLE)
    luaL_error(L, "'package.searchers' must be a table");
  /*  遍历已发现可用的加载器 */
  for (i = 1; ; i++) {
	  //searchers表中没有更多的加载器，加载失败
    if (lua_rawgeti(L, 3, i) == LUA_TNIL) {  
      lua_pop(L, 1);  
      luaL_pushresult(&msg);  
      luaL_error(L, "module '%s' not found:%s", name, lua_tostring(L, -1));
    }
	//压入形参，并执行函数
    lua_pushstring(L, name);
    lua_call(L, 1, 2);  
	//索引为-2的是函数，表示加载器加载块成功，直接返回
    if (lua_isfunction(L, -2))  
      return;  
	//索引为-2的是字符串，添加该错误描述
    else if (lua_isstring(L, -2)) {  
      lua_pop(L, 1); 
      luaL_addvalue(&msg); 
    }
    else
      lua_pop(L, 2);  
  }
}