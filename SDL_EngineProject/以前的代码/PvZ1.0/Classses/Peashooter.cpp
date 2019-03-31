#include "Peashooter.h"
#include "MainLua.h"
const std::string Peashooter::NAME = "Peashooter";
Peashooter::Peashooter()
{
}
Peashooter::~Peashooter()
{
}
bool Peashooter::init()
{
	auto pL = MainLua::getInstance();
	m_nCurHP = m_nHitPoint = pL->getDoubleFromTable(NAME,"hp");
	initInterval();
	//绑定Sprite
	bindSprite(Sprite::createWithSpriteFrameName("Peashooter1.png"));
	//运行初始动画
	this->getSprite()->runAction(this->onNormalAction());
	return true;
}
FiniteTimeAction*Peashooter::onNormalAction()
{
	if(m_pSprite)
	{
		return  Entity::createAnimation("Peashooter%d.png",1,13,0.09,-1);
	}
	return nullptr;
}
FiniteTimeAction*Peashooter::onSkillAction()
{
	return nullptr;
}
void Peashooter::onHurt()
{
}
void Peashooter::onDead()
{
}
void Peashooter::initInterval()
{
	//技能CD 每次都重新获取
	m_interval = MainLua::getInstance()->getDoubleFromTable(NAME,"skillCD");
}
PlantType Peashooter::getPlantType()const
{
	return PlantType::kPlantType_Shooter;
}
std::string Peashooter::getName()const
{
	return NAME;
}