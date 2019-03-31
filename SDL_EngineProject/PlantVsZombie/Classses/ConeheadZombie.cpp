#include "ConeheadZombie.h"

ConeheadZombie::ConeheadZombie()
	:m_bGarnishryDead(false)
{
}

ConeheadZombie::~ConeheadZombie()
{
}

ConeheadZombie*ConeheadZombie::create(const string&zombieName)
{
	auto zombie = new ConeheadZombie();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool ConeheadZombie::init(const string&zombieName)
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

void ConeheadZombie::onGarnishryDead()
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

void ConeheadZombie::setSpriteFlipX(bool flipX)
{
	this->getSprite()->setFlipX(flipX);

	this->judgeInnerSpritePos();
}

void ConeheadZombie::changeState(State state)
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
	}
	else if (m_state == State::AttackDead)
	{
		animationName = "ZombieLostHeadAttack";
		
		this->showZombieHead();
	}
	if (animationName.empty())
	{
		return;
	}
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	ZombieBase::changeAnimation(animation);
}

void ConeheadZombie::showZombieHead()
{
	//调整位置
	Point bornPos = this->getPosition();
	Size size = this->getContentSize();
	bool flipX = this->getSprite()->isFlipX();

	if (flipX)
		bornPos.x -= size.width/4.f;
	else
		bornPos.x += size.width/3.f;

	m_pDelegate->showZombieHead(this->getZombieName(),bornPos,this->getTag(),flipX);
}

void ConeheadZombie::judgeInnerSpritePos()
{
	Size size = this->getContentSize();
	bool flipX = m_pSprite->isFlipX();

	Point pos;
	//对僵尸内部精灵进行稍微调整
	if (m_bGarnishryDead)
	{
		if (flipX)
			pos = Point(size.width/2.f + 45.f,size.height/2.f);
		else
			pos = Point(size.width/2.f + 15.f,size.height/2.f);
	}
	else
	{
		if (flipX)
			pos = Point(size.width/2.f + 60.f,size.height/2.f);
		else
			pos = Point(size.width/2.f,size.height/2.f);
	}

	m_pSprite->setPosition(pos);
}

void ConeheadZombie::onButterDebuffEnter(const Point&pos)
{
	auto startPos = pos;

	if (!m_bGarnishryDead)
	{
		startPos += Point(15.f,8.f);
	}
	Zombie::onButterDebuffEnter(startPos);
}

void ConeheadZombie::onButterDebuffExit()
{
	Zombie::onButterDebuffExit();
}