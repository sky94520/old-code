#include "PaperZombie.h"

PaperZombie::PaperZombie()
	:m_bIsAngry(false)
{
}

PaperZombie::~PaperZombie()
{
}

PaperZombie*PaperZombie::create(const string&zombieName)
{
	auto zombie = new PaperZombie();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool PaperZombie::init(const string&zombieName)
{
	//正常动画
	this->setZombieName(zombieName);
	//获取站立状态贴图
	int status = m_bIsAngry ? 0 : 1;
	auto animationName = StringUtils::format("%sWalk%d",m_zombieName.c_str(),status);

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
	Speed*speed = Speed::create(animate,1.f);
	
	speed->setTag(ANIMATION_TAG);

	m_pSprite->runAction(speed);
	//设置为行走状态
	m_state = State::Walk;

	return true;
}

void PaperZombie::changeState(State state)
{
	//状态没有发生改变，直接退出
	if (m_state == state)
		return ;

	m_state = state;
	string animationName;
	int status = m_bIsAngry ? 0 : 1;

	if (m_state == State::Walk)
	{
		animationName = StringUtils::format("%sWalk%d",m_zombieName.c_str(),status);
	}
	else if (m_state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack%d",m_zombieName.c_str(),status);
	}
	else if (m_state == State::WalkDead)
	{
		animationName = StringUtils::format("%sLostHeadWalk%d",m_zombieName.c_str(),status);

		this->showZombieHead();
	}
	else if (m_state == State::AttackDead)
	{
		animationName = StringUtils::format("%sLostHeadAttack%d",m_zombieName.c_str(),status);
		
		this->showZombieHead();
	}
	//改变的状态没有动画，则直接返回
	if (animationName.empty())
	{
		return;
	}
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	ZombieBase::changeAnimation(animation);
}

void PaperZombie::showZombieHead()
{
	//调整位置
	Point bornPos = this->getPosition();
	Size size = this->getContentSize();

	m_pDelegate->showZombieHead(this->getZombieName(),bornPos,this->getTag(),false);
}

float PaperZombie::getCurSpeed()const
{
	auto speed = ZombieBase::getCurSpeed();

	if (m_bIsAngry)
		speed *= 2.f;

	return speed;
}

void PaperZombie::onGarnishryDead()
{
	//当前死亡，则不再执行
	if (this->getHitPoint() <= 0)
		return ;

	m_bIsAngry = true;
	//改为站立状态
	this->changeState(State::Idle);
	//停止原先动画
	m_pSprite->stopActionByTag(ANIMATION_TAG);
	//报纸掉落动画
	auto animationName = "PaperZombieLostNewspaper";
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	Animate*animate = Animate::create(animation);
	auto speed = Speed::create(animate,1.f);
	speed->setTag(ANIMATION_TAG);

	if (this->isDuringDeceleration())
		speed->setSpeed(0.7f);

	DelayTime*delay = DelayTime::create(animate->getDuration());
	CallFunc*end = CallFunc::create([this]()
	{
		this->changeState(State::Walk);
	});
	auto seq = Sequence::createWithTwoActions(delay,end);

	this->stopAllActions();
	//开始动画
	m_pSprite->runAction(speed);
	this->runAction(seq);
}

void PaperZombie::onCRPDead()
{
	this->setDead(true);

	bool flipX = this->getSprite()->isFlipX();
	//显示死亡动画
	m_pDelegate->showZombieDie(this->getZombieName(),this->getPosition(),this->getTag(),flipX);
}

void PaperZombie::onButterDebuffEnter(const Point&pos)
{
	Zombie::onButterDebuffEnter(pos - Point(-15.f,0.f));
}

void PaperZombie::onButterDebuffExit()
{
	Zombie::onButterDebuffExit();
}