#include "CherryBomb.h"
#include "MainLua.h"
const std::string CherryBomb::NAME = "CherryBomb";
CherryBomb::CherryBomb()
{
}
CherryBomb::~CherryBomb()
{
}
bool CherryBomb::init()
{
	auto pL = MainLua::getInstance();
	m_nCurHP = m_nHitPoint = pL->getDoubleFromTable(NAME,"hp");
	initInterval();
	//绑定Sprite
	bindSprite(Sprite::createWithSpriteFrameName("CherryBomb1.png"));

	this->getSprite()->runAction(onNormalAction());
	return true;
}
FiniteTimeAction*CherryBomb::onNormalAction()
{
	if(m_pSprite)
	{
		return  Entity::createAnimation("CherryBomb%d.png",1,7,0.1,1);
	}
	return nullptr;
}
FiniteTimeAction*CherryBomb::onSkillAction()
{
	if(m_pSprite)
	{
		return  Entity::createAnimation("Boom.png",1,1,0.2f,1);
	}
	return nullptr;
}
void CherryBomb::onHurt()
{
}
void CherryBomb::onDead()
{
}
void CherryBomb::initInterval()
{
	//技能CD 每次都重新获取
	m_interval = MainLua::getInstance()->getDoubleFromTable(NAME,"skillCD");
}
PlantType CherryBomb::getPlantType()const
{
	return PlantType::kPlantType_Bomb;
}
std::string CherryBomb::getName()const
{
	return NAME;
}