#include "SunFlower.h"
#include "MainLua.h"
const std::string SunFlower::NAME = "SunFlower";
SunFlower::SunFlower()
{
}
SunFlower::~SunFlower()
{
}
bool SunFlower::init()
{
	auto pL = MainLua::getInstance();
	m_nCurHP = m_nHitPoint = pL->getDoubleFromTable(NAME,"hp");
	initInterval();
	//��Sprite
	bindSprite(Sprite::createWithSpriteFrameName("SunFlower1.png"));
	//���г�ʼ����
	this->getSprite()->runAction(this->onNormalAction());
	return true;
}
FiniteTimeAction*SunFlower::onNormalAction()
{
	if(m_pSprite)
	{
		return  Entity::createAnimation("SunFlower%d.png",1,18,0.11,-1);
	}
	return nullptr;
}
FiniteTimeAction*SunFlower::onSkillAction()
{
	if(m_pSprite)
	{
		//����̫������
		CallFunc*show = CallFunc::create([&]()
		{
			m_pSprite->setColorMod(0xee,0xc9,0x00);
		});
		DelayTime*delayTime = DelayTime::create(1.5f);
		CallFunc*hide = CallFunc::create([&]()
		{
			m_pSprite->setColorMod(255,255,255);
			//m_bRunningSkill = false;
		});
		return Sequence::create(show,delayTime,hide,NULL);
	}
}
void SunFlower::onHurt()
{
}
void SunFlower::onDead()
{
}
void SunFlower::initInterval()
{
	//����CD ÿ�ζ����»�ȡ
	m_interval = MainLua::getInstance()->getDoubleFromTable(NAME,"skillCD");
}
PlantType SunFlower::getPlantType()const
{
	return PlantType::kPlantType_Producer;
}
std::string SunFlower::getName()const
{
	return NAME;
}