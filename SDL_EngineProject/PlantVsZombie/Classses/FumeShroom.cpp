#include "FumeShroom.h"
#include "ZombieBase.h"

FumeShroom::FumeShroom()
	:m_elapsed(0.f),m_duration(0.f)
	,m_bShooting(false)
{
}

FumeShroom::~FumeShroom()
{
}

FumeShroom*FumeShroom::create(const string&plantName)
{
	auto plant = new FumeShroom();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool FumeShroom::init(const string&plantName)
{
	//设置正常的动画
	this->setPlantName(plantName);
	//设置正常动画
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//设置贴图
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);
	
	this->bindSpriteWithAnimate(animate);

	auto size = m_pSprite->getContentSize();
	//重新设置位置
	m_pSprite->setAnchorPoint(Point(0.5f,0.5f));
	m_pSprite->setPosition(Point(size.width/3.f * 2.f,size.height/2.f));
	//设置状态为正常状态
	m_state = State::Normal;

	return true;
}

void FumeShroom::shoot()
{
	this->changeState(State::Attack);
	//发动攻击
	int row = m_pCarrier->getRow();
	auto size = this->getContentSize();
	auto pos = this->getPosition() + Point(size.width/2.f,0.f);

	m_pDelegate->addFumeShroomBullet(m_nDamage,row,pos,this->getAttackScope());
}

void FumeShroom::updateAtkState(float dt)
{
	m_elapsed += dt;
	//攻击一次
	if (!m_bShooting)
	{
		this->shoot();
		m_bShooting = true;
	}

	if (m_elapsed >= m_duration)
	{
		m_elapsed = 0.f;

		this->changeState(State::Normal);
		//重置攻击
		m_bShooting = false;
	}
}

void FumeShroom::changeState(State state)
{
	if (m_state == state)
		return;

	m_state = state;

	string animationName;
	auto plantName = this->getPlantName();
	Animation*animation = nullptr;

	if (state == State::Normal)
	{
		animationName = plantName;
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::Sleeping)
	{
		animationName = StringUtils::format("%sSleep",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_duration = animation->getDuration();
	}

	if (animation == nullptr)
		return;
	//停止原先的动画
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//创建动画
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->getSprite()->runAction(animate);
}