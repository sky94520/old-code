#include "PuffShroom.h"

PuffShroom::PuffShroom()
{
}

PuffShroom::~PuffShroom()
{
}

PuffShroom*PuffShroom::create(const string& plantName)
{
	auto plant = new PuffShroom();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool PuffShroom::init(const string& plantName)
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
	//����״̬Ϊ����״̬
	m_state = State::Normal;

	return true;
}

void PuffShroom::updateAtkState(float dt)
{
	int damage = this->getDamage();
	int row = m_pCarrier->getRow();
	//ȷ������λ��
	auto bornPos = this->getPosition();
	Size size = this->getContentSize();

	bornPos.x += size.width/2;
	bornPos.y += size.height/4;
	//ֱ�ӽ��й���
	m_pDelegate->addShroomBullet(damage,row,bornPos,this->getAttackScope());
	//��������
	this->changeState(State::Normal);
}

void PuffShroom::changeState(State state)
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
	//ֹͣԭ�ȵĶ���
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//��������
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->getSprite()->runAction(animate);
}