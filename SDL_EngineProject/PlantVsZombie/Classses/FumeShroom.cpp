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
	//���������Ķ���
	this->setPlantName(plantName);
	//������������
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//������ͼ
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);
	
	this->bindSpriteWithAnimate(animate);

	auto size = m_pSprite->getContentSize();
	//��������λ��
	m_pSprite->setAnchorPoint(Point(0.5f,0.5f));
	m_pSprite->setPosition(Point(size.width/3.f * 2.f,size.height/2.f));
	//����״̬Ϊ����״̬
	m_state = State::Normal;

	return true;
}

void FumeShroom::shoot()
{
	this->changeState(State::Attack);
	//��������
	int row = m_pCarrier->getRow();
	auto size = this->getContentSize();
	auto pos = this->getPosition() + Point(size.width/2.f,0.f);

	m_pDelegate->addFumeShroomBullet(m_nDamage,row,pos,this->getAttackScope());
}

void FumeShroom::updateAtkState(float dt)
{
	m_elapsed += dt;
	//����һ��
	if (!m_bShooting)
	{
		this->shoot();
		m_bShooting = true;
	}

	if (m_elapsed >= m_duration)
	{
		m_elapsed = 0.f;

		this->changeState(State::Normal);
		//���ù���
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
	//ֹͣԭ�ȵĶ���
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//��������
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->getSprite()->runAction(animate);
}