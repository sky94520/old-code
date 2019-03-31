#include "PotatoMine.h"
#include "MainLua.h"
const std::string PotatoMine::NAME = "PotatoMine";
PotatoMine::PotatoMine()
	:m_bReady(false)
{
}
PotatoMine::~PotatoMine()
{
}
bool PotatoMine::init()
{
	auto pL = MainLua::getInstance();
	m_nCurHP = m_nHitPoint = pL->getDoubleFromTable(NAME,"hp");
	m_interval = 15.f;
	//initInterval();
	//绑定Sprite
	bindSprite(Sprite::createWithSpriteFrameName("PotatoMineNotReady.png"));

	//this->getSprite()->runAction(onNormalAction());
	return true;
}
FiniteTimeAction*PotatoMine::onNormalAction()
{
	if(m_pSprite)
	{
		return Entity::createAnimation("PotatoMine%d.png",1,8,0.2f,-1);
	}
	return nullptr;
}
FiniteTimeAction*PotatoMine::onSkillAction()
{
	if(m_pSprite)
	{
		return Entity::createAnimation("PotatoMine_mashed.png",1,1,0.2f,1);
	}
	return nullptr;
}
void PotatoMine::onHurt()
{
}
void PotatoMine::onDead()
{
}
void PotatoMine::initInterval()
{
	//技能CD 每次都重新获取
	m_interval = MainLua::getInstance()->getDoubleFromTable(NAME,"skillCD");
}
PlantType PotatoMine::getPlantType()const
{
	return PlantType::kPlantType_Bomb;
}
std::string PotatoMine::getName()const
{
	return NAME;
}