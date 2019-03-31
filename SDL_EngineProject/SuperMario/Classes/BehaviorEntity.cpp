#include "BehaviorEntity.h"
#include "MoveBehavior.h"
BehaviorEntity::BehaviorEntity()
	:m_pMoveBehavior(nullptr)
{
}
BehaviorEntity::~BehaviorEntity()
{
	m_pMoveBehavior = nullptr;
}
void BehaviorEntity::performMove(float dt)
{
	if(m_pMoveBehavior)
	{
		m_pMoveBehavior->performMove(this,dt);
		auto velocity = this->getVelocity();
		if(velocity.x > 0)
			this->getSprite()->setFlipX(false);
		else
			this->getSprite()->setFlipX(true);
	}
}
void BehaviorEntity::setMoveBehavior(MoveBehavior*moveBehavior)
{
	m_pMoveBehavior = moveBehavior;
}
MoveBehavior*BehaviorEntity::getMoveBehavior()
{
	return m_pMoveBehavior;
}