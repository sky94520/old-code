#include "ScreenDoorZombie.h"

ScreenDoorZombie::ScreenDoorZombie()
{
}

ScreenDoorZombie::~ScreenDoorZombie()
{
}

ScreenDoorZombie* ScreenDoorZombie::create(const string& zombieName)
{
	auto zombie = new ScreenDoorZombie();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool ScreenDoorZombie::init(const string& zombieName)
{
	this->setZombieName(zombieName);
	//获取站立状态贴图
	auto animationName = StringUtils::format("%sWalk",m_zombieName.c_str());
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//设置贴图
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();

	this->bindSpriteWithSpriteFrame(firstFrame);
	//稍微调整一下位置
	this->judgeInnerSpritePos();
	//运行站立动画
	auto animate = Animate::create(animation);
	Speed*speed = Speed::create(animate,1.f);
	speed->setTag(ANIMATION_TAG);

	m_pSprite->runAction(speed);
	//设置为行走状态
	m_state = State::Walk;
	return true;
}

void ScreenDoorZombie::onGarnishryDead()
{
	//设置名称
	this->setZombieName(m_nextZombieName);
	m_bGarnishryDead = true;

	auto oldState = m_state;

	m_state = State::None;
	//稍微调整位置
	this->judgeInnerSpritePos();

	this->changeState(oldState);
	//显示路障掉落动作
	Point pos = this->getPosition();
	Size size = this->getContentSize();

	pos.x += size.width/4;
	pos.y -= size.height/2;

	m_pDelegate->showGarnishryFallAction(m_pGarnishry,pos,this->getTag(),false);
}

void ScreenDoorZombie::changeState(State state)
{
	//状态没有发生改变，直接退出
	if (m_state == state)
		return ;
	//如果饰品已经死亡，则调用父类的方法
	if (m_bGarnishryDead)
	{
		Zombie::changeState(state);
		return;
	}
	m_oldState = m_state;
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
	else if (m_state == State::WalkDead)
	{
		this->showZombieHead();

		animationName = StringUtils::format("%sLostHeadWalk",m_zombieName.c_str());
	}
	else if (m_state == State::AttackDead)
	{
		this->showZombieHead();

		animationName = StringUtils::format("%sLostHeadAttack",m_zombieName.c_str());
	}
	if (animationName.empty())
	{
		return;
	}
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	ZombieBase::changeAnimation(animation);
}

void ScreenDoorZombie::judgeInnerSpritePos()
{
}