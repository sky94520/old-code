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
	//�򿪻����Ŀ�
	luaL_openlibs(m_pLuaState);
	//��lua��ע�ắ��
	//lua_register(m_pLuaState,
	return true;
}