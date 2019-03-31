#include "Monster.h"
#include "MainLua.h"
#include "Player.h"
#include "GlobalFunctions.h"
Monster::Monster()
	:m_ID(""),m_name(""),m_description("")
	,m_nHP(0),m_nCurHP(0),m_nDamage(0),m_nAgility(0)
	,m_nGold(0)
{
}
Monster::~Monster()
{
}
bool Monster::init(const std::string&id)
{
	m_ID = id;
	m_name = MainLua::getInstance()->getStringFromTable(id.c_str(),"name");
	m_description = MainLua::getInstance()->getStringFromTable(id.c_str(),"description");
	m_nCurHP = m_nHP = MainLua::getInstance()->getIntegerFromTable(id.c_str(),"hp");
	m_nDamage = MainLua::getInstance()->getIntegerFromTable(id.c_str(),"damage");
	m_nAgility = MainLua::getInstance()->getIntegerFromTable(id.c_str(),"agility");
	m_nGold = MainLua::getInstance()->getIntegerFromTable(id.c_str(),"gold");
	return true;
}
void Monster::attack(Player*pPlayer)
{
	//todo
	auto pL = MainLua::getInstance()->getLuaState();
	//把表放到栈顶
	lua_getglobal(pL,m_ID.c_str());
	//找到对应函数
	lua_pushstring(pL,"attack");
	lua_gettable(pL,-2);
	//压入参数
	lua_pushstring(pL,"player");
	int num = 1;
	//todo
	//执行函数
	if(lua_pcall(pL,num,0,0) != LUA_OK)
	{
		printf("error:%s",luaL_checkstring(pL,-1));
		GlobalFunctions::getcha();
	}
}
void Monster::hurt(int damage)
{
	int hp = m_nCurHP - damage;
	std::cout<<m_ID<<"受到攻击，HP-"<<damage<<std::endl;
	//死亡
	if(hp <= 0)
	{
		hp = 0;
		dead();
	}
	m_nCurHP = hp;
}
void Monster::dead()
{
	std::cout<<m_ID<<"已死亡"<<std::endl;
}
bool Monster::isDead()const
{
	return m_nCurHP <= 0;
}