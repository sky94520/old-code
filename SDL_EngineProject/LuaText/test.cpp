#include "lua.h"

static int ll_require (lua_State *L)
{
  //��ȡ��Ӧ������
  const char *name = luaL_checkstring(L, 1);
  //����Ѿ����ع��ˣ����ټ���
  lua_settop(L, 1);  
  lua_getfield(L, LUA_REGISTRYINDEX, "_LOADED");
  lua_getfield(L, 2, name);  
  if (lua_toboolean(L, -1))  
    return 1;  
  //��ջ�е���lua_getfile()�Ľ��
  lua_pop(L, 1);
  //���ּ������������ֳɹ���ջ��Ӧ�ô���ģ��(����Ϊfunction)���ַ���
  findloader(L, name);
  //ѹ���Ҫ�Ĳ�����ջ
  lua_pushstring(L, name);  
  lua_insert(L, -2);  
  //���м�����������ģ��
  lua_call(L, 2, 1);  
  /* _LOADED[name] = returned value */
  if (!lua_isnil(L, -1))  
    lua_setfield(L, 2, name);
  //û�з���ֵ���� _LOADED[name] = true
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
  //����ʼ���ýṹ��
  luaL_buffinit(L, &msg);
  /* �� 'package.searchers' �ŵ�����Ϊ3��ջ�� */
  if (lua_getfield(L, lua_upvalueindex(1), "searchers") != LUA_TTABLE)
    luaL_error(L, "'package.searchers' must be a table");
  /*  �����ѷ��ֿ��õļ����� */
  for (i = 1; ; i++) {
	  //searchers����û�и���ļ�����������ʧ��
    if (lua_rawgeti(L, 3, i) == LUA_TNIL) {  
      lua_pop(L, 1);  
      luaL_pushresult(&msg);  
      luaL_error(L, "module '%s' not found:%s", name, lua_tostring(L, -1));
    }
	//ѹ���βΣ���ִ�к���
    lua_pushstring(L, name);
    lua_call(L, 1, 2);  
	//����Ϊ-2���Ǻ�������ʾ���������ؿ�ɹ���ֱ�ӷ���
    if (lua_isfunction(L, -2))  
      return;  
	//����Ϊ-2�����ַ�������Ӹô�������
    else if (lua_isstring(L, -2)) {  
      lua_pop(L, 1); 
      luaL_addvalue(&msg); 
    }
    else
      lua_pop(L, 2);  
  }
}