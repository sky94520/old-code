#include "Player.h"
#include "TextureManager.h"
#include "Weapon.h"
#include "UserDefault.h"
#include "DynamicData.h"
#include "Monster.h"
Player::Player()
	:position(),m_pWeapon(nullptr),m_nHP(0)
	,m_nCurHP(0),m_nAgility(0),m_nAtk(0)
{
	//读取存档 最大HP
	m_nHP = m_nCurHP = UserDefault::getInstance()->getIntegerForKey("hp",50);
	//敏捷
	m_nAgility = UserDefault::getInstance()->getIntegerForKey("agility",1);
	//攻击力
	m_nAtk = UserDefault::getInstance()->getIntegerForKey("atk",1);
	//当前装备
	std::string weaponID = UserDefault::getInstance()->getStringForKey("weapon","");
	//装备当前装备
	if(!weaponID.empty())
	{
		auto pItems = DynamicData::getInstance()->getPackages();
		for(int i=0;i<pItems->size();i++)
			if(weaponID == pItems->at(i)->getStringID())
			{
				m_pWeapon = dynamic_cast<Weapon*>(pItems->at(i));
				m_pWeapon->setOwner(this);
				break;
			}
	}
}
Player::~Player()
{
	//保存到文件xml中
	UserDefault::getInstance()->setIntegerForKey("hp",m_nHP);
	UserDefault::getInstance()->setIntegerForKey("agility",m_nAgility);
	UserDefault::getInstance()->setIntegerForKey("atk",m_nAtk);
	if(m_pWeapon)
		UserDefault::getInstance()->setStringForKey("weapon",m_pWeapon->getStringID());
}
void Player::bindSprite(char sprite)
{
	this->sprite = sprite;
}
void Player::setPosition(int x,int y)
{
	position.x = x;
	position.y = y;
}
void Player::setPosition(const Point&pos)
{
	position.x = pos.x;
	position.y = pos.y;
}
Point Player::getPosition()const
{
	return position;
}
void Player::render()
{
	TextureManager::getInstance()->draw(position.x,position.y,sprite);
}
void Player::attack(Monster*pMonster)
{
	auto realAtk = m_nAtk;
	//如果有武器
	if(m_pWeapon)
	{
		m_pWeapon->use();
		realAtk += m_pWeapon->getAtk();
	}
	pMonster->hurt(realAtk);
}
void Player::hurt(int damage)
{
	int hp = m_nCurHP - damage;
	//死亡
	if(hp <= 0)
	{
		hp = 0;
		dead();
	}
	m_nCurHP = hp;
}
void Player::dead()
{
}
bool Player::isDead()const
{
	return m_nCurHP <= 0;
}
void Player::setWeapon(Weapon*weapon)
{
	auto wea = this->getWeapon();
	if(wea)
		wea->setOwner(nullptr);

	weapon->setOwner(this);
	m_pWeapon = weapon;
}
Weapon* Player::getWeapon()const
{
	return m_pWeapon;
}