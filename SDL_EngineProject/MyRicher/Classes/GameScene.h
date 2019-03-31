#ifndef __GameScene_H__
#define __GameScene_H__
#include <string>
#include "lua/lua.h"
#include "SDL_Engine/SDL_Engine.h"
using namespace std;
using namespace SDL;
class MapLayer;
class PlayerLayer;
class PanelLayer;
class ScriptLayer;
/*游戏当前状态*/
enum class GameState
{
	Normal,
	Script,
};

class GameScene : public Scene
{
private:
	MapLayer* m_pMapLayer;
	PlayerLayer* m_pPlayerLayer;
	PanelLayer * m_pPanelLayer;
	ScriptLayer *m_pScriptLayer;

	GameState m_gameState;
	lua_State* m_pLuaState;
private:
	static GameScene * m_pInstance;
private:
	GameScene();
	~GameScene();
	bool init();
private:
	void loadResources();
	void initlizeLevel(const string& levelName);
	void initlizeScript();
public:
	static GameScene* getInstance();
	static void purge();
	void update(float dt);
	void scriptWaitEnd();
	//游戏状态
	GameState getGameState()const;
	void setGameState(GameState gameState);
public://private
	void goBtnCallback();
public://脚本相关
	//获取table对应键的值 只能是基础数据类型
	Value getValueOfTable(const string&table,const string& key,Value::Type type = Value::Type::STRING);
	//执行对应table的函数 第一个参数为table本身 变长参数一律使用Value*
	vector<Value> luaPcall(const string&table,const string&func,int nresult,...);
	//协程 开始或者恢复 TODO
	vector<Value> luaResume(const string& func,...);
	//加载lua脚本
	int luaLoadFile(const string& filename);
	//执行脚本
	int luaDoString(const string& str);
	int luaDoFile(const string& filename);
	//执行脚本
	int luaPcall(int nargs, int nresults, int msgh);
	int luaGetTop()const;
	void luaSetTop(int index);
	
	int luaLen(int index);
	//获取全局变量
	int luaGetglobal(const string& name);
	int luaGettable(int index);
	const char* luaPushstring(const string& s);
	void luaPushinteger(lua_Integer number);
	void luaPushnumber(lua_Number number);
	void luaPushboolean(bool var);

	const char*luaLCheckString(int index);
	bool luaToBoolean(int index);
	lua_Integer luaLCheckInteger(int index);
	lua_Number luaLCheckNumber(int index);
	
	int luaType(int index);
};
#endif