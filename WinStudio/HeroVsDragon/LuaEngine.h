#ifndef __LuaEngine_H__
#define __LuaEngine_H__
#include<string>
#include<cmath>

#include "lua/lua.hpp"

/*ֻ�Ǳ����˶�lua_State������,һ������ֻ��һ��*/
class LuaEngine
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
	//���ؽű���ִ��
	int dofile(const std::string&fn);
	//�ӱ��л�ȡ��Ӧ������(��ʱ��ô�ƺ�)
	const char* getStringFromTable(const char*tableName,const char*key);
	int getIntegerFromTable(const char*tableName,const char*key);
	float getFloatFromTable(const char*tableName,const char*key);
};
#endif