#include "Plane.h"
Plane::Plane()
	:m_pDelegate(nullptr),m_nBulletNum(0)
{
}
Plane::~Plane()
{
}
bool Plane::init()
{
	this->bindSprite(Sprite::createWithSpriteFrameName("smallplane_1.png"));
	return true;
}
bool Plane::shoot()
{
	//限制子弹的发射
	if(m_nBulletNum > 0)
	{
		--m_nBulletNum;
		m_pDelegate->shooting(this,kBulletType_Common);
		return true;
	}
	return false;
}
void Plane::update(float dt)
{
	Entity::update(dt);
}
void Plane::onDead()
{
}
PlaneDelegate*Plane::getDelegate()const
{
	return m_pDelegate;
}
void Plane::setDelegate(PlaneDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}