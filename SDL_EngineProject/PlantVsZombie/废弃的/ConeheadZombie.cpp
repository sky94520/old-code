#include "ConeheadZombie.h"
#include "Terrain.h"
#include "Plant.h"
#include "MoveBehavior.h"
#include "HpBar.h"

ConeheadZombie::ConeheadZombie()
	:m_pInnerZombie(nullptr),m_elapsed(0.f)
{
}

ConeheadZombie::~ConeheadZombie()
{
}

ConeheadZombie*ConeheadZombie::create(const string&zombieName,ZombieBase*zombieBase)
{
	auto zombie = new ConeheadZombie();

	if (zombie && zombie->init(zombieName,zombieBase))
		zombie->autoRelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool ConeheadZombie::init(const string&zombieName,ZombieBase*zombieBase)
{
	//创建贴图
	this->setZombieName(zombieName);
	//获取站立状态贴图
	auto animationName = StringUtils::format("%sIdle",zombieName.c_str());
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//设置贴图
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();

	m_pSprite = Sprite::createWithSpriteFrame(firstFrame);

	auto size = m_pSprite->getContentSize();

	m_pSprite->setPosition(size.width/2,size.height/2);

	this->setContentSize(size);
	this->addChild(m_pSprite);
	//运行站立动画
	auto animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	m_pSprite->runAction(animate);
	//设置为站立状态
	m_state = State::Idle;
	//添加僵尸
	m_pInnerZombie = zombieBase;
	m_pInnerZombie->setPosition(size.width/2 + 10.f,size.height/2);
	//TODO 设置微不显示
	//m_pInnerZombie->setVisible(false);
	this->addChild(m_pInnerZombie);

	return true;
}

void ConeheadZombie::setDelegate(ZombieDelegate*pDelegate)
{
	ZombieBase::setDelegate(pDelegate);
	m_pInnerZombie->setDelegate(pDelegate);
}

void ConeheadZombie::setAim(Terrain*plant)
{
	ZombieBase::setAim(plant);
	m_pInnerZombie->setAim(plant);
}

void ConeheadZombie::setMoveBehavior(MoveBehavior*behavior)
{
	ZombieBase::setMoveBehavior(behavior);
	//m_pInnerZombie->setMoveBehavior(behavior);
}

bool ConeheadZombie::isDying()const
{
	return m_pInnerZombie->isDying();
}

bool ConeheadZombie::isDead()const
{
	return m_pInnerZombie->isDead();
}

void ConeheadZombie::update(float dt)
{
	//当前路障还没死亡
	if (this->getHitPoint() > 0)
	{
		this->coneheadUpdate(dt);
	}
	//路障已经死亡，则调用内部僵尸进行更新
	{
		m_pInnerZombie->update(dt);
	}
}

float ConeheadZombie::getCurSpeed()const
{
	float speed = m_fBaseSpeed;

	if (this->getHitPoint() <= 0)
		speed = m_pInnerZombie->getCurSpeed();

	return speed;
}

Rect ConeheadZombie::getCollisionBoundingBox()const
{
	Rect rect = this->getSprite()->getSpriteFrameRect();
	//进行x y坐标的更新
	auto r = this->getBoundingBox();

	rect.origin.x += r.origin.x;
	rect.origin.y += r.origin.y;

	return rect;
}

int ConeheadZombie::hurtHook(int baseDamage,AttackType attackType)
{
	int damage;
	//路障还没死亡 TODO
	if (this->getHitPoint() > 0)
	{
		damage = baseDamage;
	}
	else
	{
		damage = 0;
		m_pInnerZombie->hurt(baseDamage,attackType);
		//m_pInnerZombie->hurtHook(baseDamage,attackType);
	}

	return damage;
}

void ConeheadZombie::onHurt()
{
	if (this->getHitPoint() > 0)
	{
		return;
	}
	else
	{
		m_pInnerZombie->onHurt();
	}
}

void ConeheadZombie::onDead()
{
	//路障死亡
	//不显示当前的僵尸
	m_pSprite->setVisible(false);
	m_pHpBar->setVisible(false);
	//显示内部僵尸
	m_pInnerZombie->setVisible(true);
}

void ConeheadZombie::changeState(State state)
{
	//状态没有发生改变，直接退出
	if (m_state == state)
		return ;

	m_state = state;
	string animationName;

	if (m_state == State::Walk)
	{
		animationName = StringUtils::format("%sWalk",m_zombieName.c_str());
	}
	else if (m_state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack",m_zombieName.c_str());
	}
	//停止原先的动画
	this->getSprite()->stopActionByTag(ANIMATION_TAG);

	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->getSprite()->runAction(animate);
}

void ConeheadZombie::coneheadUpdate(float dt)
{
	//TODO 当前如果处于站立状态，则直接跳转到行走状态
	if (m_state == State::Idle)
	{
		this->changeState(State::Walk);
	}
	//当前存在攻击目标
	else if (m_pAim != nullptr)
	{
		if (m_pAim->getInnerPlant() != nullptr)
		{
			this->changeState(State::Attack);
			m_elapsed += dt;
			//到达攻击时间
			if (m_elapsed >= this->getColdDownTime())
			{
				m_elapsed -= this->getColdDownTime();
				//进行攻击
				auto topPlant = m_pDelegate->getTopPlant(m_pAim);
				topPlant->hurt(this->getDamage());
			}
		}
		else//重新计时
		{
			this->clearAim();
			m_elapsed = 0.f;
		}

	}
	//没有攻击目标，行走
	else if (m_pAim == nullptr)
	{
		this->changeState(State::Walk);
	}
	if (m_pMoveBehavior != nullptr &&
		m_state == State::Walk)
	{
		m_pMoveBehavior->performMove(this);
	}
}