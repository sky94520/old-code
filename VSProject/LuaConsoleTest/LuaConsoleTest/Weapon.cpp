#include "Weapon.h"
#include "lua/lua.h"
#include "MainLua.h"
#include "Player.h"
#include "MainLua.h"
#include "Monster.h"
#include "GlobalFunctions.h"

Weapon::Weapon()
	:m_nAtk(0),m_pOwner(nullptr)
	,m_nCurDurability(0),m_nDurability(0)
{
}
Weapon::~Weapon()
{
}
bool Weapon::init(const std::string&stringID)
{
	m_stringID = stringID;
	//获取表中的武器内容
	m_name = MainLua::getInstance()->getStringFromTable(stringID.c_str(),"name");
	m_description = MainLua::getInstance()->getStringFromTable(stringID.c_str(),"description");
	m_nAtk = MainLua::getInstance()->getIntegerFromTable(stringID.c_str(),"damage");
	m_nPrice = MainLua::getInstance()->getIntegerFromTable(stringID.c_str(),"price");
	return true;
}
void Weapon::attack()
{
	//todo
	auto pL = MainLua::getInstance()->getLuaState();
	//把表放到栈顶
	lua_getglobal(pL,m_stringID.c_str());
	//找到对应函数
	lua_pushstring(pL,"attack");
	lua_gettable(pL,-2);
	//压入参数
	lua_pushstring(pL,"player");
	//todo
	//执行函数
	if(lua_pcall(pL,1,0,0) != LUA_OK)
	{
		printf("error:%s",luaL_checkstring(pL,-1));
		GlobalFunctions::getcha();
	}
}
void Weapon::setOwner(Player*pPlayer)
{
	m_pOwner = pPlayer;
}
Player*Weapon::getOwner()const
{
	return m_pOwner;
}
bool Weapon::isEquipped()const
{
	return m_pOwner;
}
void Weapon::use()
{
	//耐久度-1
	m_nCurDurability -= 1;
	this->attack();
}
std::string Weapon::toString()const
{
	std::stringstream str;
	str<<"名称:"<<this->getName()<<std::endl;
	str<<"描述:"<<this->getDescription()<<std::endl;
	str<<"伤害:"<<this->getAtk()<<std::endl;
	str<<"价值:"<<this->getPrice()<<std::endl;

	return str.str();
}