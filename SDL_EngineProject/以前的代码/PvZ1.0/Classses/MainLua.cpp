#include "MainLua.h"
MainLua*MainLua::m_pInstance = nullptr;
MainLua::MainLua()
	:m_pScriptContext(nullptr)
{
	m_pScriptContext = luaL_newstate();
	//打开所有基本库
	luaL_openlibs(m_pScriptContext);
}
MainLua::~MainLua()
{
	lua_close(m_pScriptContext);
}
void MainLua::purge()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
MainLua*MainLua::getInstance()
{
	if(m_pInstance == nullptr)
		m_pInstance = new MainLua();
	return m_pInstance;
}
lua_State*MainLua::getLuaState()const
{
	return m_pScriptContext;
}
bool MainLua::dofile(const std::string&filename)
{
	return luaL_dofile(m_pScriptContext,filename.c_str());
}
const char*MainLua::getStringFromTable(const std::string&tableName,const std::string&key)
{
	/*把当前栈清空，如果指定的index大于之前
	栈的大小，那么多余的空间会用nil填充*/
	lua_settop(m_pScriptContext,0);
	//把表放到栈顶
	lua_getglobal(m_pScriptContext,tableName.c_str());
	//检测栈顶是否是table
	if(lua_istable(m_pScriptContext,-1))
	{
		lua_pushstring(m_pScriptContext,key.c_str());
		lua_gettable(m_pScriptContext,-2);
		return lua_tostring(m_pScriptContext,-1);
	}
	return "";
}
int MainLua::getIntegerFromTable(const std::string&tableName,const std::string&key)
{
	lua_settop(m_pScriptContext,0);
	//把表放到栈顶
	lua_getglobal(m_pScriptContext,tableName.c_str());
	//检测栈顶是否是table
	if(lua_istable(m_pScriptContext,-1))
	{
		lua_pushstring(m_pScriptContext,key.c_str());
		lua_gettable(m_pScriptContext,-2);
		return lua_tonumber(m_pScriptContext,-1);
	}
}
double MainLua::getDoubleFromTable(const std::string&tableName,const std::string&key)
{
	lua_settop(m_pScriptContext,0);
	//把表放到栈顶
	lua_getglobal(m_pScriptContext,tableName.c_str());
	//检测栈顶是否是table
	if(lua_istable(m_pScriptContext,-1))
	{
		lua_pushstring(m_pScriptContext,key.c_str());
		lua_gettable(m_pScriptContext,-2);
		return lua_tonumber(m_pScriptContext,-1);
	}
	return 0.0;
}
bool MainLua::getBoolFromTable(const std::string&tableName,const std::string&key)
{
	lua_settop(m_pScriptContext,0);
	//把表放到栈顶
	lua_getglobal(m_pScriptContext,tableName.c_str());
	//检测栈顶是否是table
	if(lua_istable(m_pScriptContext,-1))
	{
		lua_pushstring(m_pScriptContext,key.c_str());
		lua_gettable(m_pScriptContext,-2);
		return lua_toboolean(m_pScriptContext,-1);
	}
	return false;
}