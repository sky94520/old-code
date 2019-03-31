#include "Squash.h"
#include "ZombieBase.h"

float Squash::s_jumpHeight = 110.f;

Squash::Squash()
	:m_state(State::Normal),m_scope(0.f)
	,m_elapsed(0.f),m_duration(0.f)
	,m_pAimZombie(nullptr),m_nDamage(0)
{
}

Squash::~Squash()
{
	SDL_SAFE_RELEASE_NULL(m_pAimZombie);
}

Squash*Squash::create(const string& plantName)
{
	auto plant = new Squash();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Squash::init(const string& plantName)
{
	this->setPlantName(plantName);

	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	animate->setTag(ANIMATION_TAG);

	this->bindSpriteWithAnimate(animate);
	//���õ�ǰ״̬
	m_state = State::Normal;

	return true;
}

void Squash::updateHook(float dt)
{
	if (m_state == State::Normal)
	{
		this->updateNormalState(dt);
	}
	else if (m_state == State::Left || m_state == State::Right)
	{
		this->updateLeftOrRightState(dt);
	}
	else if (m_state == State::LeftEnd || m_state == State::RightEnd)
	{
		printf("leftEnd or RightEnd");
	}
	else if (m_state == State::Attack)
	{
		this->updateAttackState(dt);
	}
	else if (m_state == State::AttackEnd)
	{
		this->updateAttackEndState(dt);
	}
}

void Squash::updateNormalState(float dt)
{
	//�����и����Ƿ��н�ʬ
	auto row = this->getRow();
	//���þ���λ��
	Rect rect;
	rect.origin = this->getPosition();
	rect.size = this->getContentSize();
	rect.size.width = m_scope;

	rect.origin.x -= m_scope/2.f;
	rect.origin.y -= rect.size.height/2.f;

	auto zombie = m_pDelegate->findFirstCollidedZombie(row,rect);
	//���ֽ�ʬ ���ҽ�ʬ����
	if (zombie != nullptr && zombie->getHitPoint() > 0)
	{
		//���ý�ʬ����ֲ��ĺδ�
		auto delta = this->getPositionX() - zombie->getPositionX();

		State nextState = State::Normal;

		if (delta < 0.f)
		{
			nextState = State::Right;
		}
		else
			nextState = State::Left;
		//�ı�״̬
		this->changeState(nextState);
		//���浱ǰ�Ľ�ʬ
		m_pAimZombie = zombie;
		SDL_SAFE_RETAIN(m_pAimZombie);
	}
}

void Squash::updateLeftOrRightState(float dt)
{
	m_elapsed += dt;
	//����ת����ʱ��
	if (m_elapsed >= m_duration)
	{
		m_elapsed = 0.f;
		State nextState;
		//��ǰ�Ľ�ʬ�����ţ�����й���׼��
		if (m_pAimZombie->getHitPoint() > 0)
		{
			nextState = State::Attack;
		}
		else//��ʬ�Ѿ����������ٽ��й���
		{
			SDL_SAFE_RELEASE_NULL(m_pAimZombie);

			if (m_state == State::Left)
				nextState = State::LeftEnd;
			else if (m_state == State::Right)
				nextState = State::RightEnd;
		}
		//�ı�״̬
		this->changeState(nextState);

		if (nextState == State::Attack)
		{
			//��ȡĿ��λ��
			auto delta = m_pAimZombie->getPosition() - this->getPosition();

			auto jumpBy = JumpBy::create(0.7f,Point(delta.x/2.f,-s_jumpHeight),0,1);

			m_duration = jumpBy->getDuration();
			//���ж���
			this->runAction(EaseIn::create(jumpBy,0.3f));
		}
	}
}

void Squash::updateAttackState(float dt)
{
	m_elapsed += dt;

	if (m_elapsed >= m_duration)
	{
		m_elapsed = 0.f;

		this->changeState(State::AttackEnd);
		//����
		//��ȡĿ��λ��
		auto delta = m_pAimZombie->getPositionX() - this->getPositionX();

		auto jumpBy = JumpBy::create(0.7f,Point(delta/2.f,s_jumpHeight),0,1);

		m_duration = jumpBy->getDuration();
		//���ж���
		this->runAction(EaseOut::create(jumpBy,0.3f));
	}
}

void Squash::updateAttackEndState(float dt)
{
	m_elapsed += dt;

	if (m_elapsed >= m_duration)
	{
		m_elapsed = 0.f;

		Rect rect = this->getCollisionBoundingBox();

		m_pDelegate->addBoom(m_nDamage,this->getRow(),rect);
		//����
		m_nHitPoint = 0;
		this->setDead(true);
	}
}

void Squash::changeState(State state)
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
	else if (state == State::Left || state == State::LeftEnd
		|| state == State::Right || state == State::RightEnd
		|| state == State::Attack || m_state == State::AttackEnd)
	{
		if (state == State::Left)
			animationName = StringUtils::format("%sLeft",plantName.c_str());
		else if (state == State::LeftEnd)
			animationName = StringUtils::format("%sLeftEnd",plantName.c_str());
		else if (state == State::Right)
			animationName = StringUtils::format("%sRight",plantName.c_str());
		else if (state == State::RightEnd)
			animationName = StringUtils::format("%sRightEnd",plantName.c_str());
		else if (state == State::Attack)
			animationName = StringUtils::format("%sAttack",plantName.c_str());
		else if (state == State::AttackEnd)
			animationName = StringUtils::format("%sAttackEnd",plantName.c_str());

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

