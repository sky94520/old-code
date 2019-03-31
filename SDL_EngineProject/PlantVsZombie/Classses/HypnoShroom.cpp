#include "HypnoShroom.h"
#include "ZombieBase.h"

HypnoShroom::HypnoShroom()
	:m_state(State::Normal)
	,m_pAim(nullptr)
{
}

HypnoShroom::~HypnoShroom()
{
	SDL_SAFE_RELEASE_NULL(m_pAim);
}

HypnoShroom* HypnoShroom::create(const string& plantName)
{
	auto plant = new HypnoShroom();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool HypnoShroom::init(const string& plantName)
{
	this->setPlantName(plantName);
	
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	animate->setTag(ANIMATION_TAG);
	this->bindSpriteWithAnimate(animate);

	m_state = State::Normal;
	return true;
}

void HypnoShroom::eatenByZombie(ZombieBase*zombie)
{
	if (m_state == State::Sleeping)
		return ;
	m_pAim = zombie;
	//暂时添加引用
	SDL_SAFE_RETAIN(zombie);
}

void HypnoShroom::updateNotSleeping(float dt)
{
	if (m_pAim != nullptr)
	{
		m_pDelegate->confuseZombie(m_pAim);

		SDL_SAFE_RELEASE_NULL(m_pAim);
		//魅惑菇死亡
		this->setHitPoint(0);
		this->setDead(true);
	}
}

void HypnoShroom::onSleepingEnter()
{
	this->changeState(State::Sleeping);
}

void HypnoShroom::onSleepingExit()
{
	this->changeState(State::Normal);
}

void HypnoShroom::changeState(State state)
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
	if (animation == nullptr)
		return;
	//停止原先的动画
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//创建动画
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->getSprite()->runAction(animate);
}