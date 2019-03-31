#ifndef __LuaEngine_H__
#define __LuaEngine_H__
#include<string>
#include<cmath>
#include "SDL_Engine/SDL_Engine.h"
#include "lua/lua.h"
using namespace SDL;

/*ֻ�Ǳ����˶�lua_State������,һ������ֻ��һ��*/
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
	//���ؽű���ִ��
	int dofile(const std::string&fn);
	//�ӱ��л�ȡ��Ӧ������(��ʱ��ô�ƺ�)
	const char* getStringFromTable(const char*tableName,const char*key);
	int getIntegerFromTable(const char*tableName,const char*key);
	float getFloatFromTable(const char*tableName,const char*key);
};
#endif