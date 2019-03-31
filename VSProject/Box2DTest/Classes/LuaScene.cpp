#include "LuaScene.h"
#include "lua/lua.h"
#include "DebugDraw.h"
LuaScene::LuaScene()
	:m_pLuaState(nullptr)
{
}
LuaScene::~LuaScene()
{
}
bool LuaScene::init()
{
	m_pLuaState = luaL_newstate();
	//打开基本的库
	luaL_openlibs(m_pLuaState);
	//在lua中注册函数
	//lua_register(m_pLuaState,
	return true;
}