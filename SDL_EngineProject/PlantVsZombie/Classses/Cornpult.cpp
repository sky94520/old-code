#include "Cornpult.h"

Cornpult::Cornpult()
	:m_bIsButter(false)
{
}

Cornpult::~Cornpult()
{
}

Cornpult*Cornpult::create(const string&plantName)
{
	auto plant = new Cornpult();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Cornpult::init(const string&plantName)
{
	this->setPlantName(plantName);
	//������������
	int index = m_bIsButter ? 1 : 0;
	auto animationName = StringUtils::format("%s%d",plantName.c_str(),index);
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//������ͼ
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();
	m_pSprite = Sprite::createWithSpriteFrame(firstFrame);
	
	auto size = m_pSprite->getContentSize();
	//����λ��
	m_pSprite->setPosition(Point(size.width/3.f,size.height/4.f));

	this->setContentSize(size);
	this->addChild(m_pSprite);
	//�������ж���
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);
	this->getSprite()->runAction(animate);
	//����״̬Ϊ����״̬
	m_state = State::Normal;

	return true;
	return true;
}

void Cornpult::changeState(State state)
{
	if (m_state == state)
		return ;

	m_state = state;

	string animationName;
	auto plantName = this->getPlantName();
	Animation*animation = nullptr;
	//�����Ƿ��ǻ�����������ͬ�Ķ���
	int index = m_bIsButter ? 1 : 0;

	if (state == State::Normal)
	{
		animationName = StringUtils::format("%s%d",plantName.c_str(),index);
		//ֹͣԭ�ȵĶ���
		this->getSprite()->stopActionByTag(ANIMATION_TAG);

		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack%d",plantName.c_str(),index);
		//ֹͣԭ�ȵĶ���
		this->getSprite()->stopActionByTag(ANIMATION_TAG);
	
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_duration = animation->getDuration();
	}
	else if (state == State::AttackEnd)
	{
		animationName = StringUtils::format("%sAttackEnd",plantName.c_str());
		//ֹͣԭ�ȵĶ���
		this->getSprite()->stopActionByTag(ANIMATION_TAG);
	
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	
		m_duration = animation->getDuration();
	}
	if (animation != nullptr)
	{
		auto animate = Animate::create(animation);
		animate->setTag(ANIMATION_TAG);

		this->getSprite()->runAction(animate);
	}
}

void Cornpult::shoot()
{
	//�����ӵ�
	auto damage = m_bIsButter ? m_nDamage * 4 : m_nDamage;

	auto pos = this->getPosition();
	auto row = m_pCarrier->getRow();

	Size size = this->getContentSize();

	pos.y -= size.height/2.f;

	m_pDelegate->addCornpultBullet(m_pAimZombie,m_bIsButter,damage,row,pos);
}

void Cornpult::shootEndHook()
{
	//���й����ж�
	double scope = RANDOM_0_1();

	m_bIsButter = scope < 0.8 ? false : true;
}