#include "DynamicData.h"
#include "LuaEngine.h"

DynamicData*DynamicData::m_pInstance = nullptr;
DynamicData::DynamicData()
	:m_nAtkTimes(0),m_nAtkAllTimes(0),m_nAnswerTimes(0)
{
}
DynamicData::~DynamicData()
{
}
DynamicData*DynamicData::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new DynamicData();
	}
	return m_pInstance;
}
void DynamicData::purge()
{
	CC_SAFE_DELETE(m_pInstance);
}
void DynamicData::initlize()
{
	auto luaState = LuaEngine::getInstance()->getLuaState();
	//清空栈顶
	lua_settop(luaState,0);
	//获取Level表
	lua_getglobal(luaState,"Level");
	//把表中的表放到栈顶
	lua_pushstring(luaState,"restriction");
	lua_gettable(luaState,-2);
	//获取restriction表中的元素
	lua_pushstring(luaState,"times");
	lua_gettable(luaState,-2);

	m_nAtkTimes = m_nAtkAllTimes = lua_tonumber(luaState,-1);
	//读取限制条件中的鱼
	//清空栈顶
	lua_settop(luaState,0);
	//获取Level表
	lua_getglobal(luaState,"Level");
	//把表中的表放到栈顶
	lua_pushstring(luaState,"restriction");
	lua_gettable(luaState,-2);
	//获取restriction表中的元素
	lua_pushstring(luaState,"needFishes");
	lua_gettable(luaState,-2);
	auto needFishes = lua_tostring(luaState,-1);
	
	auto len = strlen(needFishes);
	char*text = new char[len + 1];
	
	strncpy(text,needFishes,len+1);
	//text[len + 1] = '\0';
	//分析限制条件并赋值
	initlizeNeedFishes(text);
	
	delete[] text;
	//发出更新通知
	//NotificationCenter::getInstance()->postNotification("dynamic data",NULL);
	//回答问题的次数，目前设置为1，只能回答一次
	m_nAnswerTimes = 1;
}
void DynamicData::clean()
{
	m_nAnswerTimes = 1;
	m_nAtkTimes = m_nAtkAllTimes = 0;
	m_needFishes.clear();
}
void DynamicData::initlizeNeedFishes(char*text)
{
	char*p = nullptr;
	char*split = ",";
	p = strtok(text,split);

	while(p)
	{
		int key = 0,value = 0;
		sscanf(p,"%d %d",&key,&value);
		m_needFishes.insert(std::make_pair(key,value));

		p = strtok(NULL,split);
	}
}
map<int,int>& DynamicData::getNeedfulFishes()
{
	return m_needFishes;
}
bool DynamicData::reduceAtkTimes()
{
	m_nAtkTimes--;
	NotificationCenter::getInstance()->postNotification("dynamic data",NULL);
	
	return m_nAtkTimes > 0;
}
void DynamicData::addAtkTimes(int times)
{
	m_nAtkTimes += times;
	NotificationCenter::getInstance()->postNotification("dynamic data",NULL);
}
bool DynamicData::reduceFish(int id)
{
	bool bRet = true;
	for(auto iter = m_needFishes.begin();iter != m_needFishes.end();++iter)
	{
		auto ID = iter->first;
		auto count = iter->second;
		if(ID == id)
		{
			if(count > 0)
			{
				iter->second--;
				NotificationCenter::getInstance()->postNotification("dynamic data",NULL);
				if(iter->second > 0)
					bRet = false;
			}
		}
		else
		{
			if(count > 0)
				bRet = false;
		}
	}
	return bRet;
}
int DynamicData::getLevelCount()const
{
	//前提:加载了main.lua
	auto luaState = LuaEngine::getInstance()->getLuaState();
	//获取LevelCount字段
	lua_settop(luaState,0);
	lua_getglobal(luaState,"LevelCount");
	if(lua_isnumber(luaState,-1))
		return lua_tonumber(luaState,-1);
	//发生错误，返回无效值
	return -1;
}