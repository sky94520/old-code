#include "Zombie.h"
#include "Plant.h"
#include "MoveBehavior.h"

Zombie::Zombie()
	:m_state(State::None),m_nType(1)
	,m_oldState(State::None)
{
}

Zombie::~Zombie()
{
}

Zombie*Zombie::create(const string&zombieName)
{
	auto zombie = new Zombie();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool Zombie::init(const string&zombieName)
{
	this->setZombieName(zombieName);
	//设置类型todo
	m_nType = 1;
	//获取行走状态贴图
	auto animationName = StringUtils::format("%sWalk%02d",m_zombieName.c_str(),m_nType);
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//设置贴图
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();
	this->bindSpriteWithSpriteFrame(firstFrame);
	//运行动画
	auto animate = Animate::create(animation);
	Speed*speed = Speed::create(animate,1.f);
	speed->setTag(ANIMATION_TAG);

	m_pSprite->runAction(speed);
	//设置为行走状态
	m_state = State::Walk;

	return true;
}

void Zombie::updateAlive(float dt)
{
	if (m_state == State::Idle)
		return;
	//当前存在攻击目标
	if (m_pAim != nullptr)
	{
		this->changeState(State::Attack);
		
		this->eatAim(dt);
	}
	else//不存在攻击目标则重新计时 并且行走
	{
		this->clearAim();
		this->changeState(State::Walk);
	}
}

bool Zombie::isCanMove()const
{
	if (m_state == State::Walk || m_state == State::WalkDead)
	{
		return true;
	}
	return false;
}

void Zombie::onNormalDead()
{
	if (m_state == State::Walk)
		changeState(State::WalkDead);
	else if (m_state == State::Attack)
		changeState(State::AttackDead);
}

void Zombie::changeState(State state)
{
	//状态没有发生改变，直接退出
	if (m_state == state)
		return ;
	m_oldState = m_state;
	m_state = state;
	string animationName;

	if (m_state == State::Walk)
	{
		animationName = StringUtils::format("%sWalk%02d",m_zombieName.c_str(),m_nType);
	}
	else if (m_state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack",m_zombieName.c_str());
	}
	else if (m_state == State::WalkDead)
	{
		animationName = "ZombieLostHead";

		this->showZombieHead();
	}
	else if (m_state == State::AttackDead)
	{
		animationName = "ZombieLostHeadAttack";
		
		this->showZombieHead();
	}
	if (animationName.empty())
	{
		return ;
	}

	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	ZombieBase::changeAnimation(animation);
}

void Zombie::showZombieHead()
{
	//调整位置
	Point bornPos = this->getPosition();
	Size size = this->getContentSize();

	bornPos.x += size.width/4.f;

	m_pDelegate->showZombieHead(this->getZombieName(),bornPos,this->getTag(),false);
}

void Zombie::onButterDebuffEnter(const Point&pos)
{
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//添加黄油特效TODO
	m_pDelegate->addButterSplat(pos + Point(0,20.f),this->getLocalZOrder(),this->getUniqueID());
}

void Zombie::onButterDebuffExit()
{
	ZombieBase::onButterDebuffExit();
	//当前没死亡，则还原动画
	if (this->getHitPoint() > 0)
	{
		m_state = State::None;

		this->changeState(m_oldState);
	}
}

void Zombie::onIceDebuffExit()
{
	ZombieBase::onButterDebuffExit();
	//当前没死亡，则还原动画
	if (this->getHitPoint() > 0)
	{
		m_state = State::None;

		this->changeState(m_oldState);
	}
}