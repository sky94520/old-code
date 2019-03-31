#include "Pumpkin.h"

Pumpkin::Pumpkin()
	:m_state(State::Normal)
{
}

Pumpkin::~Pumpkin()
{
}

Pumpkin*Pumpkin::create(const string& plantName)
{
	auto plant = new Pumpkin();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Pumpkin::init(const string& plantName)
{
	if (Defender::init())
	{
		this->setPlantName(plantName);
		//设置正常动画
		auto animationName = plantName;
		auto animation = AnimationCache::getInstance()->getAnimation(animationName);
		Animate*animate = Animate::create(animation);
		animate->setTag(ANIMATION_TAG);

		this->bindSpriteWithAnimate(animate);
		//设置当前状态
		m_state = State::Normal;
	}
	return true;
}

void Pumpkin::updateHook(float dt)
{
}

void Pumpkin::onHurt()
{
	Plant::onHurt();

	auto curHP = this->getHitPoint();

	auto cracked = 3;
	if (curHP != 0)
	{
		cracked = m_nMaxHitPoint/curHP;
	}
	State state = State::None;

	if (cracked == 1)
	{
		state = State::Normal;
	}
	else if (cracked == 2)
	{
		state = State::Damage1;
	}
	else if (cracked == 3)
	{
		state = State::Damage2;
	}
	this->changeState(state);
}

void Pumpkin::changeState(State state)
{
	if (m_state == State::None || m_state == state)
		return;
	m_state = state;

	string animationName;
	auto plantName = this->getPlantName();
	Animation*animation = nullptr;

	if (state == State::Normal)
	{
		animationName = plantName;
	}
	else if (state == State::Damage1)
	{
		animationName = StringUtils::format("%sDamage1",plantName.c_str());
	}
	else if (state == State::Damage2)
	{
		animationName = StringUtils::format("%sDamage2",plantName.c_str());
	}

	if (!animationName.empty())
	{
		animation = AnimationCache::getInstance()->getAnimation(animationName);
		auto animate = Animate::create(animation);
		animate->setTag(ANIMATION_TAG);
		//停止原先动画
		this->getSprite()->stopActionByTag(ANIMATION_TAG);

		this->getSprite()->runAction(animate);
	}
}