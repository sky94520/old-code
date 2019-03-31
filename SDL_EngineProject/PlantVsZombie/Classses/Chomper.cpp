#include "Chomper.h"
#include "ZombieBase.h"

Chomper::Chomper()
	:m_scope(0.f),m_nDamage(0)
	,m_state(State::Normal)
	,m_elapsed(0.f),m_duration(0.f)
	,m_pAimZombie(nullptr)
{
}

Chomper::~Chomper()
{
}

Chomper*Chomper::create(const string&plantName)
{
	auto plant = new Chomper();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Chomper::init(const string&plantName)
{
	this->setPlantName(plantName);
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	animate->setTag(ANIMATION_TAG);
	//�󶨾���
	this->bindSpriteWithAnimate(animate);
	//����λ��
	auto size = this->getContentSize();
	this->getSprite()->setPosition(Point(size.width/3 * 2,size.height/3));
	//���õ�ǰ״̬
	m_state = State::Normal;

	return true;
}

void Chomper::updateHook(float dt)
{
	//����״̬���н�ʬ�ļ��
	if (m_state == State::Normal)
	{
		this->updateNormalState(dt);
	}
	//�ڹ�����ʼ�����������Զ�ת�빥������״̬
	else if (m_state == State::AttackStart)
	{
		m_elapsed += dt;
		//�����������ٴν��м��
		if (m_elapsed >= m_duration)
		{
			//Ŀ�꽩ʬѪ��С�ڵ���0�������
			if (m_pAimZombie->getHitPoint() <= 0)
			{
				SDL_SAFE_RELEASE_NULL(m_pAimZombie);
			}
			else//��Ŀ�꽩ʬ��������˺�
			{
				m_pAimZombie->hurt(m_nDamage,AttackType::Swallow);
			}
			m_elapsed = 0.f;
			this->changeState(State::AttackEnd);
		}
	}
	else if (m_state == State::AttackEnd)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			//��ǰ���ڹ���Ŀ��ת�������׶�
			if (m_pAimZombie != nullptr)
			{
				this->changeState(State::Digesting);
				SDL_SAFE_RELEASE_NULL(m_pAimZombie);
			}
			else//ת�������׶�
			{
				this->changeState(State::Normal);
			}
			m_elapsed = 0.f;
		}
	}
	//�����׶�
	else if (m_state == State::Digesting)
	{
		m_elapsed += dt;

		if (m_elapsed >= this->getColdDownTime())
		{
			this->changeState(State::Success);

			m_elapsed = 0.f;
		}
	}
	//ת�������׶�
	else if (m_state == State::Success)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			this->changeState(State::Normal);

			m_elapsed = 0.f;
		}
	}
}

void Chomper::updateNormalState(float dt)
{
	//��⽩ʬ
	int row = m_pCarrier->getRow();

	auto pos = this->getPosition();

	auto zombie = m_pDelegate->findFirstZombieOfRow(row,this->getDir(),pos);
	//��ǰ��ʬ������ ���߽�ʬ��Ѫ����= 0 ֱ���˳�
	if (zombie == nullptr || zombie->getHitPoint() <= 0)
		return;
	//�жϸý�ʬ�Ƿ���ʳ�˻�������Χ��
	auto delta = (float)SDL_fabs(pos.x - zombie->getPositionX());
	//��ǰ��ʬ�ڹ�����Χ��,��󶨽�ʬ�������빥���׶�
	if (delta < m_scope)
	{
		m_pAimZombie = zombie;
		SDL_SAFE_RETAIN(m_pAimZombie);

		m_elapsed = 0.f;

		this->changeState(State::AttackStart);
	}
}

void Chomper::changeState(State state)
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
	else if (state == State::Digesting)
	{
		animationName = StringUtils::format("%sDigest",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::AttackStart)
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
	else if (state == State::Success)
	{
		animationName = StringUtils::format("%sSuccess",plantName.c_str());
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