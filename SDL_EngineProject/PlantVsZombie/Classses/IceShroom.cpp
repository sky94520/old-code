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
	//���������Ķ���
	this->setPlantName(plantName);
	//������������
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//�������ж���
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->bindSpriteWithAnimate(animate);

	m_state = State::Normal;

	return true;
}

void IceShroom::updateNotSleeping(float dt)
{
	m_elapsed += dt;
	//����ʱ��ͱ�ը
	if (m_elapsed >= this->getColdDownTime())
	{
		this->skill();
	}
}

void IceShroom::onHurt()
{
	Plant::onHurt();

	//û��˯�� �����ɺ�������Ч
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
	//ֹͣԭ�ȵĶ���
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//��������
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->getSprite()->runAction(animate);
}

void IceShroom::skill()
{
	//��ȡ��ǰ����Ϸ����
	auto rect = m_pDelegate->getGameVisibleRect();
	//��ȡ��Ӧ�Ľ�ʬ
	auto zombies = m_pDelegate->findCollidedZombies(-1,rect);
	//Ӧ�������еĽ�ʬ
	for (auto &zombie : zombies)
	{
		if (zombie->getHitPoint() > 0)
		{
			zombie->ice(4.f);
			zombie->deceleration(AttackType::TrackAndDeceleration,10.f);
		}
	}
	//ѩ������
	m_pDelegate->showSnow();
	//�Լ�����
	this->setHitPoint(0);
	this->setDead(true);
}