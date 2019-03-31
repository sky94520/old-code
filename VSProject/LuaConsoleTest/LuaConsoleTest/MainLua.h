#ifndef __MainLua_H__
#define __MainLua_H__
#include<string>
#include<cmath>
#include "lua/lua.h"
/*ֻ�Ǳ����˶�lua_State������,һ������ֻ��һ��*/
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
	//�ӱ��л�ȡ��Ӧ������(��ʱ��ô�ƺ�)
	const char* getStringFromTable(const char*tableName,const char*key);
	int getIntegerFromTable(const char*tableName,const char*key);
};
#endif