#include "Monster.h"

Monster::Monster()
{
	m_isAlive = false;
}
Monster::~Monster(){}

bool Monster::init()
{
	return true;
}
void Monster::show()
{
	if (getSprite() != NULL)
	{
		setVisible(true);
		m_isAlive = true;
	}
}
void Monster::hide()
{
	if (getSprite() != NULL)
	{
		setVisible(false);
		reset();
		m_isAlive = false;
	}
}
void Monster::reset()
{
	if (getSprite() != NULL)
	{
		setPosition(Point(800 + CCRANDOM_0_1()*2000,200 - CCRANDOM_0_1()*100));
	}
}
bool Monster::isAlive()
{
	return m_isAlive;
}
bool Monster::isCollideWithPlayer(Player*player)
{
	Rect entityRect = player->getBoundingBox();
	Point monsterPos = getPosition();

	return entityRect.containsPoint(monsterPos);
}