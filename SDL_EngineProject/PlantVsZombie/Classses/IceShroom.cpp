#include "IceShroom.h"
#include "ZombieBase.h"

IceShroom::IceShroom()
	:m_state(State::None),m_nDamage(0)
	,m_elapsed(0.f)
{
}

IceShroom::~IceShroom()
{
}

IceShroom*IceShroom::create(const string&plantName)
{
	auto shroom = new IceShroom();

	if (shroom && shroom->init(plantName))
		shroom->autorelease();
	else
		SDL_SAFE_DELETE(shroom);

	return shroom;
}

bool IceShroom::init(const string&plantName)
{
	//设置正常的动画
	this->setPlantName(plantName);
	//设置正常动画
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//设置运行动画
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->bindSpriteWithAnimate(animate);

	m_state = State::Normal;

	return true;
}

void IceShroom::updateNotSleeping(float dt)
{
	m_elapsed += dt;
	//到达时间就爆炸
	if (m_elapsed >= this->getColdDownTime())
	{
		this->skill();
	}
}

void IceShroom::onHurt()
{
	Plant::onHurt();

	//没有睡眠 被啃噬后立即生效
	if (!this->isSleeping())
		this->skill();
}

void IceShroom::onSleepingEnter()
{
	this->changeState(State::Sleeping);
}

void IceShroom::onSleepingExit()
{
	this->changeState(State::Normal);
}

void IceShroom::changeState(State state)
{
	if (m_state == state || state == State::None)
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

	if (animation == nullptr)
		return;
	//停止原先的动画
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//创建动画
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->getSprite()->runAction(animate);
}

void IceShroom::skill()
{
	//获取当前的游戏区域
	auto rect = m_pDelegate->getGameVisibleRect();
	//获取对应的僵尸
	auto zombies = m_pDelegate->findCollidedZombies(-1,rect);
	//应用于所有的僵尸
	for (auto &zombie : zombies)
	{
		if (zombie->getHitPoint() > 0)
		{
			zombie->ice(4.f);
			zombie->deceleration(AttackType::TrackAndDeceleration,10.f);
		}
	}
	//雪花动画
	m_pDelegate->showSnow();
	//自己死亡
	this->setHitPoint(0);
	this->setDead(true);
}