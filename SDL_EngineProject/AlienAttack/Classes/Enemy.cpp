#include "Enemy.h"
#include "FlyBehavior.h"
#include "ShootBehavior.h"

Enemy::Enemy()
	:m_speed(0.f),m_bUpdate(false),m_bulletType(kBulletType_None)
	,m_elpased(0.f),m_shootInterval(-1.f),m_worth(0)
	,m_pFlyBehavior(nullptr),m_pShootBehavior(nullptr)
	,m_pDeadAction(nullptr),m_type(kEnemyType_None)
{
}
Enemy::~Enemy()
{
	SDL_SAFE_DELETE(m_pFlyBehavior);
	SDL_SAFE_DELETE(m_pShootBehavior);
	SDL_SAFE_RELEASE(m_pDeadAction);
}
bool Enemy::init()
{
	return true;
}
void Enemy::update(float dt)
{
	//飞行
	if(m_pFlyBehavior)
		m_pFlyBehavior->fly(this);
	//只有在射击行为不为空时或者射击频率小于0才进行射击更新
	if(m_pShootBehavior && m_shootInterval >= 0.f)
	{
		m_elpased += dt;
		if(m_elpased >= m_shootInterval)
		{
			m_elpased -= m_shootInterval;
			
			m_pShootBehavior->shoot(this);
		}
	}
}
void Enemy::onDead()
{
	this->getSprite()->setFlipY(false);
	//运行飞行动画后，死亡
	if(m_pDeadAction)
	{
		DelayTime*delayTime = DelayTime::create(m_pDeadAction->getDuration());
		CallFunc*end = CallFunc::create([this](){
			this->m_bDead = true;
		});
		this->stopAllActions();
		this->getSprite()->stopAllActions();

		this->runAction(Sequence::createWithTwoActions(delayTime,end));
		this->getSprite()->runAction(m_pDeadAction);
	}
	else
	{
		m_bDead = true;
	}
}
void Enemy::setFlyBehavior(FlyBehavior*behavior)
{
	SDL_SAFE_DELETE(m_pFlyBehavior);
	m_pFlyBehavior = behavior;
}
void Enemy::setShootBehavior(ShootBehavior*behavior)
{
	SDL_SAFE_DELETE(m_pShootBehavior);
	m_pShootBehavior = behavior;
}
void Enemy::reset()
{
	m_type = kEnemyType_None;
	m_bulletType = kBulletType_None;
	m_speed = 0;
	m_worth = 0;
	m_bUpdate = false;
	m_elpased = 0.f;
	m_shootInterval = 0.f;

	SDL_SAFE_RELEASE_NULL(m_pDeadAction);
	//删除行为
	SDL_SAFE_DELETE(m_pShootBehavior);
	SDL_SAFE_DELETE(m_pFlyBehavior);
	m_bDead = false;
	m_nCurHp = m_nMaxHp = 0;
	//删除精灵
	if(m_pSprite)
	{
		m_pSprite->removeFromParent();
		m_pSprite = nullptr;
	}
}