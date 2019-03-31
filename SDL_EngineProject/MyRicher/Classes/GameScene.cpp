#include "GameScene.h"
#include "MapLayer.h"
#include "PlayerLayer.h"
#include "StaticData.h"
#include "Player.h"
#include "PanelLayer.h"
#include "ScriptLayer.h"

GameScene* GameScene::m_pInstance = nullptr;

GameScene::GameScene()
	:m_pMapLayer(nullptr)
	,m_pPlayerLayer(nullptr)
	,m_pPanelLayer(nullptr)
	,m_pScriptLayer(nullptr)
	,m_gameState(GameState::Normal)
	,m_pLuaState(nullptr)
{
}

GameScene::~GameScene()
{
	StaticData::purge();

	if (m_pLuaState != nullptr)
	{
		lua_close(m_pLuaState);
		m_pLuaState = nullptr;
	}
}

bool GameScene::init()
{
	//������Դ
	this->loadResources();
	//�������ֶ���
	m_pMapLayer = MapLayer::create();
	this->addChild(m_pMapLayer);
	//����
	m_pPanelLayer = PanelLayer::create();
	this->addChild(m_pPanelLayer);
	//������ɫ��
	m_pPlayerLayer = PlayerLayer::create();
	this->addChild(m_pPlayerLayer);
	//�ű������
	m_pScriptLayer = ScriptLayer::create();
	this->addChild(m_pScriptLayer);
	//��ʼ���ؿ�
	this->initlizeLevel("map/map1.tmx");

	Director::getInstance()->getRenderer()->setRenderDrawColor(Color4B(0,255,255));
	return true;
}

void GameScene::loadResources()
{
	//����ͼƬ
	auto spriteFrameCache = Director::getInstance()->getSpriteFrameCache();
	spriteFrameCache->addSpriteFramesWithFile("sprites/resources1.xml");
}

void GameScene::initlizeLevel(const string& levelName)
{
	auto textureCache = Director::getInstance()->getTextureCache();
	//��ʼ����ͼ
	m_pMapLayer->initWithLevel(levelName);
	auto objects = m_pMapLayer->getObjectGroup()->getObjects();

	//���� ���н�ɫ�Ĵ���
	for (const auto& object : objects)
	{
		auto& valueMap = object.asValueMap();
		auto name = valueMap.at("name").asString();
		auto x = valueMap.at("x").asInt();
		auto y = valueMap.at("y").asInt();
		auto width = valueMap.at("width").asInt();
		auto height = valueMap.at("height").asInt();

		auto& properties = valueMap.at("properties").asValueMap();
		auto filename = properties.at("texture").asString();
		//��ȡ����
		auto nDir = properties.at("dir").asInt();
		auto dir = static_cast<Direction>(nDir);
		//����ͼƬ
		auto texture = textureCache->addImage(filename);
		//�и�ͼƬ�����ɶ�Ӧ����
		m_pPlayerLayer->createAnimationOfPlayer(texture,name);
		//���ɶ�Ӧ��ɫ
		auto player = Player::create(name,dir);
		player->setPosition(Point(x + width / 2,y + height / 2));
		//�������
		m_pPlayerLayer->addPlayer(player);
	}
}

void GameScene::initlizeScript()
{
	m_pLuaState = luaL_newstate();
	luaL_openlibs(m_pLuaState);
	//TODO

}

GameScene* GameScene::getInstance()
{
	if (m_pInstance == nullptr && Director::getInstance()->isRunning())
	{
		m_pInstance = new GameScene();
		m_pInstance->init();
	}
	return m_pInstance;
}

void GameScene::purge()
{
	SDL_SAFE_RELEASE_NULL(m_pInstance);
}

void GameScene::update(float dt)
{
}

void GameScene::scriptWaitEnd()
{
	//����״̬ time => none
	if (m_pScriptLayer->getWaitType() == WaitType::Time)
	{
		m_pScriptLayer->setWaitType(WaitType::None);
		//�ָ���Ӧ��Э��
		this->luaResume("");
	}
}

GameState GameScene::getGameState()const
{
	return m_gameState;
}

void GameScene::setGameState(GameState gameState)
{
	m_gameState = gameState;
}

void GameScene::goBtnCallback()
{
	//go ��ť������

}
//------------------------------------�ű�-------------------------------------
Value GameScene::getValueOfTable(const string&table,const string& key,Value::Type type)
{
	Value value;

	//��ȡ��Ӧ��table,������ջ��
	this->luaGetglobal(table);
	//����key
	this->luaPushstring(key);
	//���ݼ���ȡ��Ӧ��ֵ ����ֵΪ���ص�����
	int ret = this->luaGettable(-2);
	//��ȡջ�� Ϊnilֱ�ӷ���
	if (ret == LUA_TNIL)
		return value;

	switch (type)
	{
	case Value::Type::BOOLEAN:
	case Value::Type::INTEGER:
	{
		int n = (int)this->luaLCheckInteger(-1);
		value = Value(n);
	}break;
	case Value::Type::FLOAT:
	{
		float n = (float)this->luaLCheckNumber(-1);
		value = Value(n);
	}
	case Value::Type::STRING:

		value = Value(this->luaLCheckString(-1));break;
	}
	//���ջ
	this->luaSetTop(0);

	return value;
}

vector<Value> GameScene::luaPcall(const string&table,const string&func,int nresult,...)
{
	vector<Value> results;
	//��ȡ��Ӧ����ĺ���
	this->luaGetglobal(table);
	this->luaPushstring(func);
	this->luaGettable(-2);
	//�Զ�����table����Ϊ��һ����
	this->luaGetglobal(table);
	//�䳤����
	va_list args;

	Value *value = nullptr;
	int nargs = 0;

	va_start(args,nresult);

	while ((value = va_arg(args,Value*)) != nullptr)
	{
		//��ȡ����
		auto type = value->getType();
		switch (type)
		{
		case SDL::Value::Type::BOOLEAN:
			this->luaPushboolean(value->asBool());
			break;
		case SDL::Value::Type::BYTE:
		case SDL::Value::Type::INTEGER:
			this->luaPushinteger(value->asInt());
			break;
		case SDL::Value::Type::FLOAT:
		case SDL::Value::Type::DOUBLE:
			this->luaPushnumber(value->asFloat());
			break;
		case SDL::Value::Type::STRING:
			this->luaPushstring(value->asString());
			break;
		default:
			break;
		}
		nargs++;
	}
	va_end(args);
	//���ú���
	this->luaPcall(1 + nargs,nresult,0);
	//��ȡ����ֵ TODO
	for ( int i = -1;abs(i) <= nresult;i--)
	{
		switch (this->luaType(i))
		{
		case LUA_TBOOLEAN:results.push_back(Value(this->luaToBoolean(i)));break;
		case LUA_TNUMBER:results.push_back(Value(this->luaLCheckNumber(i)));break;
		case LUA_TSTRING:results.push_back(Value(this->luaLCheckString(i)));break;
		default:
			break;
		}
	}
	//����ű�
	this->luaSetTop(0);

	return results;
}

vector<Value> GameScene::luaResume(const string& func,...)
{
	vector<Value> results;
	//��ȡ��Ӧ�ĺ���
	if (!func.empty())
		lua_getglobal(m_pLuaState,func.c_str());
	//�䳤����
	va_list args;

	Value *value = nullptr;
	int nargs = 0;
	//�Ӻδ���ʼ
	va_start(args,func);

	while ((value = va_arg(args,Value*)) != nullptr)
	{
		//��ȡ����
		auto type = value->getType();
		switch (type)
		{
		case SDL::Value::Type::BOOLEAN:
			lua_pushboolean(m_pLuaState,value->asInt());
			break;
		case SDL::Value::Type::BYTE:
		case SDL::Value::Type::INTEGER:
			lua_pushinteger(m_pLuaState,value->asInt());
			break;
		case SDL::Value::Type::FLOAT:
		case SDL::Value::Type::DOUBLE:
			lua_pushnumber(m_pLuaState,(lua_Number)value->asFloat());
			break;
		case SDL::Value::Type::STRING:
			lua_pushstring(m_pLuaState,value->asString().c_str());
			break;
		default:
			break;
		}
		nargs++;
	}
	va_end(args);
	//�ָ�
	int result = lua_resume(m_pLuaState,nullptr,nargs);
	//����ʧ��
	if (result != LUA_OK && result != LUA_YIELD)
	{
		printf("%d%s",__LINE__,luaL_checkstring(m_pLuaState,-1));
		return results;
	}
	int nresult = this->luaGetTop();
	//��ȡ����ֵ TODO
	for ( int i = -1;abs(i) <= nresult;i--)
	{
		switch (this->luaType(i))
		{
		case LUA_TBOOLEAN:results.push_back(Value(lua_toboolean(m_pLuaState,i)));break;
		case LUA_TNUMBER:results.push_back(Value(luaL_checknumber(m_pLuaState,i)));break;
		case LUA_TSTRING:results.push_back(Value(luaL_checkstring(m_pLuaState,i)));break;
		default:
			break;
		}
	}
	//����ű�
	this->luaSetTop(0);

	return results;
}

int GameScene::luaLoadFile(const string& filename)
{
	int ret = LUA_ERRSYNTAX;
	//�ļ���Ϊ�գ�ֱ�ӷ���
	if (filename.empty())
		return ret;
	//��ȡ�ַ���
	auto text = FileUtils::getInstance()->getUniqueDataFromFile(filename);

	//���ؽű�
	if (text.get() != nullptr)
	{
		string str = text.get();
		ret = luaL_loadstring(m_pLuaState,str.c_str());
	}

	if (ret != LUA_OK)
	{
		printf("%s",luaL_checkstring(m_pLuaState,-1));
	}
	return ret;
}

int GameScene::luaDoString(const string& str)
{
	int ret = LUA_ERRSYNTAX;
	//ִ�нű�
	if (!str.empty())
	{
		ret = luaL_dostring(m_pLuaState,str.c_str());
	}

	if (ret != LUA_OK)
	{
		printf("%s",luaL_checkstring(m_pLuaState,-1));
	}

	return ret;
}

int GameScene::luaDoFile(const string& filename)
{
	int ret = LUA_ERRSYNTAX;
	//���ؽű�
	ret = this->luaLoadFile(filename);

	if (ret == LUA_OK)
	{
		ret = this->luaPcall(0,0,0);
	}

	if (ret != LUA_OK)
	{
		printf("%s",luaL_checkstring(m_pLuaState,-1));
	}

	return ret;
}

int GameScene::luaPcall(int nargs, int nresults, int msgh)
{
	auto ret = lua_pcall(m_pLuaState,nargs,nresults,msgh);

	if (ret != 0)
	{
		printf("error running function %s",lua_tostring(m_pLuaState,-1));
	}

	return ret;
}

int GameScene::luaGetTop()const
{
	return lua_gettop(m_pLuaState);
}

void GameScene::luaSetTop(int index)
{
	lua_settop(m_pLuaState,index);
}

int GameScene::luaLen(int index)
{
	lua_len(m_pLuaState,index);

	int number = this->luaLCheckInteger(-1);
	return number;
}

int GameScene::luaGetglobal(const string& name)
{
 	return lua_getglobal(m_pLuaState,name.c_str());
}

int GameScene::luaGettable(int index)
{
	return lua_gettable(m_pLuaState,index);
}

const char* GameScene::luaPushstring(const string& s)
{
	return lua_pushstring(m_pLuaState,s.c_str());
}

void GameScene::luaPushinteger(lua_Integer number)
{
	lua_pushinteger(m_pLuaState,number);
}

void GameScene::luaPushnumber(lua_Number number)
{
	lua_pushnumber(m_pLuaState,number);
}

void GameScene::luaPushboolean(bool var)
{
	return lua_pushboolean(m_pLuaState,var);
}

const char* GameScene::luaLCheckString(int index)
{
	return luaL_checkstring(m_pLuaState,index);
}

bool GameScene::luaToBoolean(int index)
{
	return lua_toboolean(m_pLuaState,index) != 0;
}

lua_Integer GameScene::luaLCheckInteger(int index)
{
	return luaL_checkinteger(m_pLuaState,index);
}

lua_Number GameScene::luaLCheckNumber(int index)
{
	return luaL_checknumber(m_pLuaState,index);
}

int GameScene::luaType(int index)
{
	return lua_type(m_pLuaState,index);
}