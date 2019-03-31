#include "FishingNet.h"
#include "StaticData.h"

FishingEntity::FishingEntity()
	:m_fishingType(FishingType::None)
{
}

FishingType FishingEntity::getFishingType()const
{
	return m_fishingType;
}

void FishingEntity::setFishingType(FishingType fishingType)
{
	m_fishingType = fishingType;
}
///--------------------------FishingNet--------------------
FishingNet::FishingNet()
	:m_nLv(0)
{
}

FishingNet::~FishingNet()
{
}
FishingNet*FishingNet::create(int lv)
{
	auto fishingNet = new FishingNet();
	if(fishingNet && fishingNet->initWithLv(lv))
		fishingNet->autoRelease();
	else
		SDL_SAFE_DELETE(fishingNet);

	return fishingNet;
}
bool FishingNet::init()
{
	FishingNet::initWithLv(1);

	return true;
}

bool FishingNet::initWithLv(int lv)
{
	m_nLv = lv;
	//��ͼ
	auto spriteFormat = STATIC_DATA_STRING("fish_net_sprite_format");
	auto spriteName = StringUtils::format(spriteFormat.c_str(),lv);

	bool bRet = Entity::bindSpriteWithSpriteFrameName(spriteName);
	
	return bRet;
}

float FishingNet::showAt()
{
	//���ö���
	auto animationFormat = STATIC_DATA_STRING("fish_net_anim_format");
	auto animationName = StringUtils::format(animationFormat.c_str(),m_nLv);

	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//���ö���
	if(animation)
	{
		auto animate = Animate::create(animation);
		this->getSprite()->runAction(animate);

		return animate->getDuration();
	}
	return 0;
}
void FishingNet::collided()
{
	auto afterHP = m_nHP - 1;
	
	if(afterHP <= 0)
	{
		afterHP = 0;
	}

	this->setHP(afterHP);
}

//-----------------------------------Laser--------------------------
bool Laser::init()
{
	m_fishingType = FishingType::Laser;

	//��ȡ��ͼ
	auto spriteName = STATIC_DATA_STRING("laser_bullet_sprite");
	 
	return this->bindSpriteWithSpriteFrameName(spriteName);
}
float Laser::showAt()
{
	//��ȡ���䶯��
	auto animationName = STATIC_DATA_STRING("laser_bullet_anim");

	auto animation = AnimationCache::getInstance()->getAnimation(animationName);

	if(animation)
	{
		Animate*animate = Animate::create(animation);

		this->getSprite()->runAction(animate);

		return animate->getDuration();
	}

	return 0.f;
}

void Laser::collided()
{
}