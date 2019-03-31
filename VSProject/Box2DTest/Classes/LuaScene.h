#ifndef __LuaScene_H__
#define __LuaScene_H__
#include "SDL_Engine/SDL_Engine.h"

using namespace SDL;
class lua_State;

class LuaScene:public Layer
{
private:
	lua_State*m_pLuaState;
public:
	LuaScene();
	~LuaScene();
	CREATE_FUNC(LuaScene);
	bool init();
};
#endif