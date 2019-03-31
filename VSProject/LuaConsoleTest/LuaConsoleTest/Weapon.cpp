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
	//��ȡ���е���������
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
	//�ѱ�ŵ�ջ��
	lua_getglobal(pL,m_stringID.c_str());
	//�ҵ���Ӧ����
	lua_pushstring(pL,"attack");
	lua_gettable(pL,-2);
	//ѹ�����
	lua_pushstring(pL,"player");
	//todo
	//ִ�к���
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
	//�;ö�-1
	m_nCurDurability -= 1;
	this->attack();
}
std::string Weapon::toString()const
{
	std::stringstream str;
	str<<"����:"<<this->getName()<<std::endl;
	str<<"����:"<<this->getDescription()<<std::endl;
	str<<"�˺�:"<<this->getAtk()<<std::endl;
	str<<"��ֵ:"<<this->getPrice()<<std::endl;

	return str.str();
}