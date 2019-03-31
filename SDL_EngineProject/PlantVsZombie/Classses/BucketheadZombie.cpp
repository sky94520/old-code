#include "BucketheadZombie.h"

BucketheadZombie::BucketheadZombie()
{
}

BucketheadZombie::~BucketheadZombie()
{
}

BucketheadZombie*BucketheadZombie::create(const string&zombieName)
{
	auto zombie = new BucketheadZombie();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool BucketheadZombie::init(const string&zombieName)
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

void BucketheadZombie::onGarnishryDead()
{
	//设置名称
	this->setZombieName(m_nextZombieName);
	m_bGarnishryDead = true;

	auto oldState = m_state;

	m_state = State::None;
	//稍微调整位置
	this->judgeInnerSpritePos();

	this->changeState(oldState);
	//显示铁桶掉落动作
	Point pos = this->getPosition();
	Size size = this->getContentSize();

	pos.x += size.width/4;
	pos.y -= size.height/2;

	m_pDelegate->showGarnishryFallAction(m_pGarnishry,pos,this->getTag(),false);
}

void BucketheadZombie::judgeInnerSpritePos()
{
	Size size = this->getContentSize();
	bool flipX = m_pSprite->isFlipX();

	Point pos;
	//对僵尸内部精灵进行稍微调整
	if (m_bGarnishryDead)
	{
		if (flipX)
			pos = Point(size.width/2.f + 40.f,size.height/2.f);
		else
			pos = Point(size.width/2.f + 15.f,size.height/2.f);
	}
	else
	{
		if (flipX)
			pos = Point(size.width/2.f + 30.f,size.height/2.f);
		else
			pos = Point(size.width/2.f,size.height/2.f);
	}

	m_pSprite->setPosition(pos);
/*	//对僵尸内部精灵进行稍微调整
	if (m_bGarnishryDead)
	{
		m_pSprite->setPosition(size.width/2.f - 15.f,size.height/2.f);
	}
	else
	{
		m_pSprite->setPosition(size.width/2.f,size.height/2.f);
	}*/
}