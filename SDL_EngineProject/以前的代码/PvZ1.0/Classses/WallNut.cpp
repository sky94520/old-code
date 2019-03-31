#include "WallNut.h"
#include "MainLua.h"
const std::string WallNut::NAME = "WallNut";
WallNut::WallNut()
	:m_status(kPlantStatus_None)
{
}
WallNut::~WallNut()
{
}
bool WallNut::init()
{
	auto pL = MainLua::getInstance();
	m_nCurHP = m_nHitPoint = pL->getDoubleFromTable(NAME,"hp");
	initInterval();
	//��Sprite
	bindSprite(Sprite::createWithSpriteFrameName("WallNut1.png"));
	
	//���г�ʼ����
	this->getSprite()->runAction(this->onNormalAction());
	return true;
}
FiniteTimeAction*WallNut::onNormalAction()
{
	if(m_pSprite)
	{
		return  Entity::createAnimation("WallNut%d.png",1,16,0.09,-1);
	}
	return nullptr;
}
FiniteTimeAction*WallNut::onSkillAction()
{
	return nullptr;
}
void WallNut::onHurt()
{
	//���Ѫ��ֵ��������ʾ��ͼƬ
	float carcke1 = 1.f/3*2*m_nHitPoint;
	float carcke2 = 1.f/3*m_nHitPoint;
	//��һ���˵�
	if(m_status == PlantStatus::kPlantStatus_None &&
		m_nCurHP <= carcke1 && m_nCurHP >= carcke2)
	{
		m_status = PlantStatus::kPlantStatus_Carcke1;
		this->getSprite()->stopAllActions();
		auto anim = Entity::createAnimation("Wallnut_cracked1-%d.png",1,11,0.1,-1);
		this->getSprite()->runAction(anim);
	}
	//�ڶ���ʧ��
	else if(m_status == PlantStatus::kPlantStatus_Carcke1 &&m_nCurHP < carcke2)
	{
		m_status = PlantStatus::kPlantStatus_Carcke2;
		this->getSprite()->stopAllActions();
		auto anim = Entity::createAnimation("Wallnut_cracked2-%d.png",1,15,0.1,-1);
		this->getSprite()->runAction(anim);
	}
}
void WallNut::onDead()
{
}
void WallNut::initInterval()
{
	//����CD ÿ�ζ����»�ȡ
	m_interval = MainLua::getInstance()->getDoubleFromTable(NAME,"skillCD");
}
PlantType WallNut::getPlantType()const
{
	return PlantType::kPlantType_Wall;
}
std::string WallNut::getName()const
{
	return NAME;
}