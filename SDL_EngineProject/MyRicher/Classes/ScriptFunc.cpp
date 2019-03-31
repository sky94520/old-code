#include "ScriptFunc.h"
#include "GameScene.h"
#include "ScriptLayer.h"
#include "StaticData.h"

static const luaL_Reg scriptlib[] = 
{
	//{"LUA_setViewPointCenter",LUA_setViewPointCenter},
	{NULL,NULL}
};
struct KeyValue
{
	char* key;
	int value;
	KeyValue(char* key,int v):key(key),value(v){}
};

bool registerFunctions(lua_State* pL)
{
	int length = sizeof(scriptlib) / sizeof(scriptlib[0]);

	for (int i = 0;i < length;i++)
	{
		lua_register(pL,scriptlib[i].name,scriptlib[i].func);
	}
	map<string,vector<KeyValue> > enumLuas;
	//×¢²áÃ¶¾ÙÌå
	enumLuas["GameState"].push_back(KeyValue("Normal",static_cast<int>(GameState::Normal)));
	enumLuas["GameState"].push_back(KeyValue("Script",static_cast<int>(GameState::Script)));

	for (auto& vec:enumLuas)
	{
		auto k = vec.first;
		auto v = vec.second;

		lua_newtable(pL);

		for (auto&keyValue:v)
		{
			LUA_ENUM(pL,keyValue.key,keyValue.value);
		}
		lua_setglobal(pL,k.c_str());
	}
	return true;
}