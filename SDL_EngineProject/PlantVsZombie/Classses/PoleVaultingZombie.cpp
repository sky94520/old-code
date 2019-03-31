#include "PoleVaultingZombie.h"
#include "Plant.h"
#include "MoveBehavior.h"
#include "PlantLayer.h"
#include "Garnishry.h"

PoleVaultingZombie::PoleVaultingZombie()
	:m_bLosePole(false),m_state(State::None)
	,m_oldState(State::None)
	,m_duration(0.f),m_elapsed(0.f)
	,m_bIsActiveForBullet(true)
{
}

PoleVaultingZombie::~PoleVaultingZombie()
{
}

PoleVaultingZombie*PoleVaultingZombie::create(const string&zombieName)
{
	auto zombie = new PoleVaultingZombie();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool PoleVaultingZombie::init(const string&zombieName)
{
	this->setZombieName(zombieName);

	//获取行走状态贴图
	auto animationName = zombieName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//设置贴图
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();

	m_pSprite = Sprite::createWithSpriteFrame(firstFrame);

	auto size = m_pSprite->getContentSize();
	//对位置进行相应的调整
	m_pSprite->setPosition(size.width/2,size.height*0.55f);

	this->setContentSize(size);
	this->addChild(m_pSprite);
	//运行动画
	auto animate = Animate::create(animation);
	Speed*speed = Speed::create(animate,1.f);
	speed->setTag(ANIMATION_TAG);

	m_pSprite->runAction(speed);
	//设置为行走状态
	m_state = m_oldState= State::Walk;

	return true;
}

void PoleVaultingZombie::updateAlive(float dt)
{
	//处于跳起状态
	if (m_state == State::Jump)
	{
		m_elapsed += dt;
		//跳起完成 检测是否碰撞的是否是高坚果
		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			this->jump2();
		}
	}//跳起2
	else if (m_state == State::Jump2)
	{
		m_elapsed += dt;
		//转到正常动画
		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			this->jumpEnd();
		}
	}
	else if (m_state == State::Walk)
	{
		//存在目标
		if (m_pAim != nullptr)
		{
			if (m_bLosePole)
				this->changeState(State::Attack);
			else
				this->jump();
		}
	}
	else if (m_state == State::Attack)
	{
		//存在目标
		if (m_pAim != nullptr)
		{
			this->eatAim(dt);
		}
		else
		{
			this->clearAim();
			this->changeState(State::Walk);
		}
	}
}

bool PoleVaultingZombie::isCanMove()const
{
	if (m_state == State::Walk || m_state == State::WalkDead)
		return true;

	return false;
}

float PoleVaultingZombie::getCurSpeed()const
{
	auto speed = ZombieBase::getCurSpeed();

	if (m_bLosePole)
		speed /= 3.f;

	return speed;
}

Rect PoleVaultingZombie::getCollisionBoundingBox()const
{
	auto rect = Character::getCollisionBoundingBox();

	if (!m_bLosePole)
	{
		rect.origin.x += rect.size.width/2.f;
		rect.origin.y += rect.size.height/2.f;
		rect.size.width /= 3 * 2;
		rect.size.height /= 2;
	}
	else
	{
		rect = ZombieBase::getCollisionBoundingBox();
	}

	return rect;
}

void PoleVaultingZombie::onNormalDead()
{
	if (m_state == State::Walk)
		changeState(State::WalkDead);
	else if (m_state == State::Attack)
		changeState(State::AttackDead);
}

void PoleVaultingZombie::onCRPDead()
{
	this->setDead(true);

	bool flipX = this->getSprite()->isFlipX();
	//显示死亡动画
	m_pDelegate->showZombieDie(this->getZombieName(),this->getPosition(),this->getTag(),flipX);
}

bool PoleVaultingZombie::isActiveForBullet()const
{
	return m_bIsActiveForBullet;
}

void PoleVaultingZombie::onButterDebuffEnter(const Point&pos)
{
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//添加黄油特效TODO
	Point startPos = pos;

	if (m_bLosePole)
	{
		startPos.x += 20.f;
	}
	else
	{
	}

	m_pDelegate->addButterSplat(startPos,this->getLocalZOrder(),this->getUniqueID());
}

void PoleVaultingZombie::onButterDebuffExit()
{
	ZombieBase::onButterDebuffExit();
	//当前没死亡，则还原动画
	if (this->getHitPoint() > 0)
	{
		m_state = State::None;

		this->changeState(m_oldState);
	}
}

void PoleVaultingZombie::onIceDebuffExit()
{
	ZombieBase::onButterDebuffExit();
	//当前没死亡，则还原动画
	if (this->getHitPoint() > 0)
	{
		m_state = State::None;

		this->changeState(m_oldState);
	}
}

void PoleVaultingZombie::jump()
{
	this->changeState(State::Jump);
	//不对子弹起碰撞
	m_bIsActiveForBullet = false;
	//当前饰品对冰块免疫
	m_pGarnishry->setImmuneForIce(true);
}

void PoleVaultingZombie::jump2()
{
	this->changeState(State::Jump2);
	//失去撑杆
	m_bLosePole = true;
	//是否能跳过去 TODO
	//直接设置位置
	auto pos = this->getPosition();
	auto size = this->getContentSize();
	auto rect = this->getCollisionBoundingBox();

	//获取当前的目标是否是植物和高坚果
	//跳过失败
	if (m_pAim != nullptr 
		&& m_pAim->getCharacterType() == CharacterType::Plant
		&& PlantLayer::isTallNut(static_cast<Plant*>(m_pAim)))
	{
		this->setPosition(pos - Point(40.f,0.f));
	}
	else
	{
		this->setPosition(pos - Point(120.f,0.f));
	}
	//清除当前目标
	this->clearAim();
}

void PoleVaultingZombie::jumpEnd()
{
	this->changeState(State::Walk);
	m_bIsActiveForBullet = true;
	//不对冰块免疫
	m_pGarnishry->setImmuneForIce(false);

	this->clearAim();
}

void PoleVaultingZombie::changeState(State state)
{
	//状态没有发生改变，直接退出
	if (m_state == state)
		return ;
	//不保存jump和jump2的状态
	if (m_state != State::Jump || m_state != State::Jump2)
		m_oldState = state;
	m_state = state;

	string animationName;
	Animation*animation = nullptr;
	auto zombieName = this->getZombieName();

	if (m_state == State::Walk)
	{
		if (m_bLosePole)
		{
			animationName = StringUtils::format("%sWalk",zombieName.c_str());
		}
		else
		{
			animationName = zombieName;
		}

		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (m_state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack",zombieName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (m_state == State::Jump)
	{
		animationName = StringUtils::format("%sJump",zombieName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
		m_duration = animation->getDuration();
	}
	else if (m_state == State::Jump2)
	{
		animationName = StringUtils::format("%sJump2",zombieName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
		m_duration = animation->getDuration();
	}
	else if (m_state == State::WalkDead)
	{
		if (!m_bLosePole)
		{
			animationName = StringUtils::format("%sLostHead",zombieName.c_str());
		}
		else
		{
			animationName = StringUtils::format("%sLostHeadWalk",zombieName.c_str());
		}
		animation = AnimationCache::getInstance()->getAnimation(animationName);
		this->showZombieHead();
	}
	else if (m_state == State::AttackDead)
	{
		animationName = StringUtils::format("%sLostHeadAttack",zombieName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		this->showZombieHead();
	}

	if (animation != nullptr)
		ZombieBase::changeAnimation(animation);
}

void PoleVaultingZombie::showZombieHead()
{
	//调整位置
	Point bornPos = this->getPosition();
	Size size = this->getContentSize();

	m_pDelegate->showZombieHead(this->getZombieName(),bornPos,this->getTag(),false);
}