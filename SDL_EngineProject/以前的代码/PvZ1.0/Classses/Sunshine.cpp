#include "Sunshine.h"
Sunshine::Sunshine()
	:m_elapsed(0.f),m_bArriveLawn(false),
	m_type(SunshineType::kSunshineType_25)
	,m_bCollected(false)
{
}
Sunshine::~Sunshine()
{
}
Sunshine* Sunshine::create(SunshineType type)
{
	auto sunshine = new Sunshine();
	if(sunshine && sunshine->init(type))
		sunshine->autoRelease();
	else
		SDL_SAFE_DELETE(sunshine);
	return sunshine;
}
bool Sunshine::init(SunshineType type)
{
	m_type = type;

	bindSprite(Sprite::createWithSpriteFrameName("Sun1.png"));
	//²¥·Å¶¯»­
	Animate*animate = Entity::createAnimation("Sun%d.png",1,22,0.08,-1);
	m_pSprite->runAction(animate);
	return true;
}
bool Sunshine::isArriveLawn()const
{
	return m_bArriveLawn;
}
void Sunshine::setArriveLawn(bool ret)
{
	m_bArriveLawn = ret;
}
bool Sunshine::isCollected()const
{
	return m_bCollected;
}
void Sunshine::setCollected(bool collected)
{
	m_bCollected = collected;
}