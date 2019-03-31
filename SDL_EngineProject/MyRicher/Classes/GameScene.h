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
/*��Ϸ��ǰ״̬*/
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
	//��Ϸ״̬
	GameState getGameState()const;
	void setGameState(GameState gameState);
public://private
	void goBtnCallback();
public://�ű����
	//��ȡtable��Ӧ����ֵ ֻ���ǻ�����������
	Value getValueOfTable(const string&table,const string& key,Value::Type type = Value::Type::STRING);
	//ִ�ж�Ӧtable�ĺ��� ��һ������Ϊtable���� �䳤����һ��ʹ��Value*
	vector<Value> luaPcall(const string&table,const string&func,int nresult,...);
	//Э�� ��ʼ���߻ָ� TODO
	vector<Value> luaResume(const string& func,...);
	//����lua�ű�
	int luaLoadFile(const string& filename);
	//ִ�нű�
	int luaDoString(const string& str);
	int luaDoFile(const string& filename);
	//ִ�нű�
	int luaPcall(int nargs, int nresults, int msgh);
	int luaGetTop()const;
	void luaSetTop(int index);
	
	int luaLen(int index);
	//��ȡȫ�ֱ���
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