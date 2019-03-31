#include "MainLua.h"
MainLua*MainLua::m_pInstance = nullptr;
MainLua::MainLua()
	:m_pScriptContext(nullptr)
{
	m_pScriptContext = luaL_newstate();
	//�����л�����
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
const char*MainLua::getStringFromTable(const char*tableName,const char*key)
{
	/*�ѵ�ǰջ��գ����ָ����index����֮ǰ
	ջ�Ĵ�С����ô����Ŀռ����nil���*/
	lua_settop(m_pScriptContext,0);
	//�ѱ�ŵ�ջ��
	lua_getglobal(m_pScriptContext,tableName);
	//���ջ���Ƿ���table
	if(lua_istable(m_pScriptContext,-1))
	{
		lua_pushstring(m_pScriptContext,key);
		lua_gettable(m_pScriptContext,-2);
		return lua_tostring(m_pScriptContext,-1);
	}
	return "";
}
int MainLua::getIntegerFromTable(const char*tableName,const char*key)
{
	auto str = getStringFromTable(tableName,key);
	return std::atoi(str);
}