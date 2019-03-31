#include "Plant.h"
#include "HpBar.h"
Plant::Plant()
	:m_nHitPoint(0),m_elapsed(0.f),m_interval(0)
	,m_nLine(-1),m_nCurHP(0)
{
}
Plant::~Plant()
{
}
void Plant::hurt(int damage)
{
	int curHP = m_nCurHP - damage;
	setCurHP(curHP);
	printf("curHP=%d,HP=%d\n",curHP,m_nCurHP);
	onHurt();
	if(curHP <= 0)
	{
		dead();
	}
}
void Plant::dead()
{
	onDead();
}
bool Plant::isDead()const
{
	return m_nCurHP <= 0;
}