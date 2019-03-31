#include "Cabbage.h"
#include "ZombieBase.h"

Cabbage::Cabbage()
{
}

Cabbage::~Cabbage()
{
}

Cabbage*Cabbage::create(const string&plantName)
{
	auto plant = new Cabbage();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Cabbage::init(const string&plantName)
{
	this->setPlantName(plantName);
	//������������
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//������ͼ
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();
	m_pSprite = Sprite::createWithSpriteFrame(firstFrame);
	
	auto size = m_pSprite->getContentSize();
	//����λ��
	m_pSprite->setPosition(Point(size.width/3.f,size.height/3.f));

	this->setContentSize(size);
	this->addChild(m_pSprite);
	//�������ж���
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);
	this->getSprite()->runAction(animate);
	//����״̬Ϊ����״̬
	m_state = State::Normal;

	return true;
}

void Cabbage::changeState(State state)
{
	if (m_state == state)
		return ;

	m_state = state;

	string animationName;
	auto plantName = this->getPlantName();
	Animation*animation = nullptr;

	if (state == State::Normal)
	{
		animationName = plantName;
		//ֹͣԭ�ȵĶ���
		this->getSprite()->stopActionByTag(ANIMATION_TAG);

		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack",plantName.c_str());
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

void Cabbage::shoot()
{
	//�����ӵ�
	auto damage = this->getDamage();
	auto pos = this->getPosition();
	auto row = m_pCarrier->getRow();

	Size size = this->getContentSize();

	pos.y -= size.height/2.f;

	m_pDelegate->addCabbageBullet(m_pAimZombie,damage,row,pos);
}

void Cabbage::shootEndHook()
{
}