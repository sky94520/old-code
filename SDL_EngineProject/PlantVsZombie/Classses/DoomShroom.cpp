#include "DoomShroom.h"
#include "Terrain.h"

DoomShroom::DoomShroom()
	:m_state(State::Normal),m_elapsed(0.f)
	,m_boomDuration(0.f),m_nDamage(0)
{
}

DoomShroom::~DoomShroom()
{
}

DoomShroom*DoomShroom::create(const string& plantName)
{
	auto plant = new DoomShroom();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool DoomShroom::init(const string& plantName)
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

void DoomShroom::updateNotSleeping(float dt)
{
	if (m_state == State::Normal)
	{
		//һ��ʱ���ת��Boom״̬
		m_elapsed += dt;

		if (m_elapsed >= this->getColdDownTime())
		{
			m_elapsed = 0.f;
			this->changeState(State::Boom);
		}
	}
	else if (m_state == State::Boom)
	{
		m_elapsed += dt;
		//����ʱ�䣬��ը
		if (m_elapsed >= m_boomDuration)
		{
			this->boom();
		}
	}
}

void DoomShroom::onSleepingEnter()
{
	this->changeState(State::Sleeping);
}

void DoomShroom::onSleepingExit()
{
	this->changeState(State::Normal);
}

void DoomShroom::onHurt()
{
	//��˯��ת��Boom
	if (! this->isSleeping())
	{
		this->changeState(State::Boom);
		m_elapsed = 0.f;
	}
}

void DoomShroom::changeState(State state)
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
	else if (state == State::Boom)
	{
		animationName = StringUtils::format("%sBoom",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_boomDuration = animation->getDuration();
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

void DoomShroom::boom()
{
	//��ǰ����û�б��ƻ������ǲݵ�
	if (!m_pCarrier->isDestroyed() && m_pCarrier->getTerrainType() == TerrainType::Lawn)
	{
		auto lawn = dynamic_cast<Lawn*>(m_pCarrier);
		//�ݵ��γɵ���
		lawn->destroyByDoomShroom();
		//չʾ��ը����
		auto pos = this->getPosition();
		pos.y += this->getContentSize().height/2;

		m_pDelegate->showBoom(pos);
		//��������
		this->setHitPoint(0);
		this->setDead(true);
		//����ȫ��ը��
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//TODO

		Rect rect = Rect(0.f,0.f,visibleSize.width,visibleSize.height);
		m_pDelegate->addBoom(m_nDamage,-1,rect);
	}
}