#include "Character.h"

const int Character::ANIMATION_TAG = 100;

Character::Character()
	:m_nHitPoint(0),m_nMaxHitPoint(0)
	,m_bDead(false),m_dir(Direction::None)
	,m_characterType(CharacterType::None)
{
}

Character::~Character()
{
}

void Character::hurt(int damage,AttackType attackType)
{
	auto afterHP = m_nHitPoint - damage;

	if (afterHP <= 0)
	{
		afterHP = 0;
		m_bDead = true;
	}
	this->setHitPoint(afterHP);

	onHurt();
}

bool Character::isDying()const
{
	return m_nHitPoint <= 0;
}

Rect Character::getCollisionBoundingBox()const
{
	Rect rect = this->getSprite()->getSpriteFrameRect();
	//进行x y坐标的更新
	auto r = this->getBoundingBox();

	rect.origin.x += r.origin.x;
	rect.origin.y += r.origin.y;

	return rect;
}