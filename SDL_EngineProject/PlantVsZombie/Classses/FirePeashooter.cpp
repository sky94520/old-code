#include "FirePeashooter.h"

FirePeashooter::FirePeashooter()
	:m_duration(0.f),m_elapsed(0.f)
{
}

FirePeashooter::~FirePeashooter()
{
}

FirePeashooter*FirePeashooter::create(const string&plantName)
{
	auto plant = new FirePeashooter();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool FirePeashooter::init(const string&plantName)
{
	this->setPlantName(plantName);

	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	animate->setTag(ANIMATION_TAG);

	this->bindSpriteWithAnimate(animate);
	//调整位置
	auto size = this->getContentSize();

	size.width *= 0.6f;
	size.height *= 0.7f;
	//重新设置位置
	this->setContentSize(size);
	this->getSprite()->setPosition(Point(size.width/3 * 2,size.height/3));

	return true;
}

void FirePeashooter::updateAttackState(float dt)
{
	m_elapsed += dt;
	//到达攻击时间，进行攻击
	if (m_elapsed >= m_duration)
	{
		int row = m_pCarrier->getRow();

		this->shootFirePeaBullet(row);

		m_duration = 0.f;
		m_elapsed = 0.f;
		//改变为攻击结束状态
		this->changeState(State::AttackEnd);
	}
}

void FirePeashooter::updateAttackEndState(float dt)
{
	m_elapsed += dt;

	if (m_elapsed >= m_duration)
	{
		m_elapsed = 0.f;
		//改变为正常状态
		this->changeState(State::Normal);
	}
}

void FirePeashooter::changeState(State state)
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
	else if (state == State::Attack)
	{
		animationName = StringUtils::format("%sAtkStart",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_duration = animation->getDuration();
	}
	else if (state == State::AttackEnd)
	{
		animationName = StringUtils::format("%sAtkEnd",plantName.c_str());
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