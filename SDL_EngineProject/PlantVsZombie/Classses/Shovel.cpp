#include "Shovel.h"
#include "StaticData.h"

Shovel::Shovel()
	:m_bSelected(false)
{
}
Shovel::~Shovel()
{
}
bool Shovel::init()
{
	auto spriteName = STATIC_DATA_STRING("shovel_sprite_name");
	this->bindSpriteWithSpriteFrameName(spriteName);

	return true;
}

bool Shovel::isSelected()const
{
	return m_bSelected;
}

void Shovel::selected()
{
	m_bSelected = true;

	auto fade = FadeOut::create(0.5f);
	auto sequence = static_cast<ActionInterval*>(Sequence::create(fade,fade->reverse(),nullptr));
	auto repeat = RepeatForever::create(sequence);
	repeat->setTag(1);

	m_pSprite->runAction(repeat);
}

void Shovel::unselected()
{
	m_bSelected = false;

	m_pSprite->stopActionByTag(1);
	m_pSprite->setOpacity(255);
}