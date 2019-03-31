#include "LuaEngine.h"
LuaEngine*LuaEngine::m_pInstance = nullptr;
LuaEngine::LuaEngine()
	:m_pScriptContext(nullptr)
{
	m_pScriptContext = luaL_newstate();
	//打开所有基本库
	luaL_openlibs(m_pScriptContext);
}
LuaEngine::~LuaEngine()
{
	lua_close(m_pScriptContext);
}
void LuaEngine::purge()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
LuaEngine*LuaEngine::getInstance()
{
	if(m_pInstance == nullptr)
		m_pInstance = new LuaEngine();
	return m_pInstance;
}
lua_State*LuaEngine::getLuaState()const
{
	return m_pScriptContext;
}
int LuaEngine::dofile(const std::string&fn)
{
	return luaL_dofile(m_pScriptContext,fn.c_str());
}
const char*LuaEngine::getStringFromTable(const char*tableName,const char*key)
{
	/*把当前栈清空，如果指定的index大于之前
	栈的大小，那么多余的空间会用nil填充*/
	lua_settop(m_pScriptContext,0);
	//把表放到栈顶
	lua_getglobal(m_pScriptContext,tableName);
	//检测栈顶是否是table
	if(lua_istable(m_pScriptContext,-1))
	{
		lua_pushstring(m_pScriptContext,key);
		lua_gettable(m_pScriptContext,-2);
		return lua_tostring(m_pScriptContext,-1);
	}
	return "";
}
int LuaEngine::getIntegerFromTable(const char*tableName,const char*key)
{
	auto str = getStringFromTable(tableName,key);
	return std::atoi(str);
}
float LuaEngine::getFloatFromTable(const char*tableName,const char*key)
{
	auto str = getStringFromTable(tableName,key);
	return std::atof(str);
}