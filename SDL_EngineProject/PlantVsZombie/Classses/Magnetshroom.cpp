#include "Magnetshroom.h"
#include "ZombieBase.h"
#include "Garnishry.h"

Magnetshroom::Magnetshroom()
	:m_state(State::Normal),m_duration(0.f)
	,m_elapsed(0.f)
{
}

Magnetshroom::~Magnetshroom()
{
}

Magnetshroom*Magnetshroom::create(const string&plantName)
{
	auto plant = new Magnetshroom();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Magnetshroom::init(const string&plantName)
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

void Magnetshroom::updateNotSleeping(float dt)
{
	if (m_state == State::Normal)
	{
		this->updateNormalState(dt);
	}
	else if (m_state == State::AttackStart)
	{
		this->updateAttackStartState(dt);
	}
	else if (m_state == State::Attacking)
	{
		this->updateAttackingState(dt);
	}
	else if (m_state == State::Digesting)
	{
		this->updateDigestState(dt);
	}
}

void Magnetshroom::onSleepingEnter()
{
	this->changeState(State::Sleeping);
}

void Magnetshroom::onSleepingExit()
{
	this->changeState(State::Normal);
}

void Magnetshroom::changeState(State state)
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
	else if (state == State::Digesting)
	{
		animationName = StringUtils::format("%sDigesting",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::AttackStart)
	{
		animationName = StringUtils::format("%sAtkStart",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_duration = animation->getDuration();
	}
	else if (state == State::Attacking)
	{
		animationName = StringUtils::format("%sAtking",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_duration = animation->getDuration();
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

void Magnetshroom::updateNormalState(float dt)
{
	Rect rect;
	//ȷ�����η�Χ
	rect.origin = this->getPosition() - Point(m_scope.width/2,m_scope.height/2);
	rect.size = m_scope;
	//���ַ�Χ���Ƿ���ڽ�ʬ
	auto zombie = m_pDelegate->findFirstZombieOfIronGarnishry(rect);
	//���ֽ�ʬ������AttackStart״̬
	if (zombie != nullptr)
	{
		this->changeState(State::AttackStart);

		m_elapsed = 0.f;
	}
}

void Magnetshroom::updateAttackStartState(float dt)
{
	Rect rect;
	//ȷ�����η�Χ
	rect.origin = this->getPosition() - Point(m_scope.width/2,m_scope.height/2);
	rect.size = m_scope;
	//���м�ʱ
	m_elapsed += dt;
	//���﹥��ʱ�䣬���Թ���
	if (m_elapsed >= m_duration)
	{
		//���ַ�Χ���Ƿ���ڽ�ʬ
		auto zombie = m_pDelegate->findFirstZombieOfIronGarnishry(rect);
		//���ֽ�ʬ�����빥��״̬
		if (zombie != nullptr)
		{
			zombie->hurt(zombie->getGarnishry()->getHitPoint(),AttackType::Magnet);
			//Attacking
			this->changeState(State::Attacking);

			m_elapsed = 0.f;
			//��Ʒ��Ч
			int uniqueID = this->getUniqueID();
			auto size = this->getContentSize();
			auto pos = this->getPosition() + Point(size.width/3,0.f);
			auto garnishry = zombie->getGarnishry();

			m_pDelegate->addGarnishryEffect(uniqueID,pos,garnishry);
		}
	}
}

void Magnetshroom::updateAttackingState(float dt)
{
	//����ʱ����Զ�ת�������׶�
	m_elapsed += dt;

	if (m_elapsed >= m_duration)
	{
		m_elapsed = 0.f;

		this->changeState(State::Digesting);
	}
}

void Magnetshroom::updateDigestState(float dt)
{
	//����ʱ����Զ�ת������״̬
	m_elapsed += dt;

	if (m_elapsed >= this->getColdDownTime())
	{
		m_elapsed = 0.f;

		this->changeState(State::Normal);
		//ɾ����Ч
		int uniqueID = this->getUniqueID();

		m_pDelegate->removeGarnishryEffect(uniqueID);
	}
}