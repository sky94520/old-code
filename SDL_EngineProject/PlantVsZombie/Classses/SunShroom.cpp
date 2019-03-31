#include "SunShroom.h"

SunShroom::SunShroom()
	:m_growUpTimeLeft(0.f),m_state(State::Normal)
	,m_elapsed(0.f),m_duration(0.f)
	,m_bSmall(true),m_elapsedSun(0.f)
{
}

SunShroom::~SunShroom()
{
}

SunShroom*SunShroom::create(const string&plantName)
{
	auto plant = new SunShroom();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool SunShroom::init(const string&plantName)
{
	this->setPlantName(plantName);
	
	auto animationName = StringUtils::format("%s2",plantName.c_str());
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	animate->setTag(ANIMATION_TAG);
	this->bindSpriteWithAnimate(animate);

	m_state = State::Normal;

	return true;
}
void SunShroom::updateNotSleeping(float dt)
{
	//����СĢ��ʱ���Գɳ���ʱ
	if (m_bSmall)
		this->growUpdate(dt);

	if (m_state == State::Normal)
	{
		m_elapsedSun += dt;
		//���������ʱ��
		if (m_elapsedSun >= this->getColdDownTime())
		{
			m_elapsedSun = 0.f;
			//�ı䵱ǰ״̬
			this->changeState(State::ProducingSun);
		}
	}
	else if (m_state == State::Growing
		|| m_state == State::ProducingSun)
	{
		m_elapsed += dt;
		//�ɳ����Զ�ת������״̬
		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			//���⹽����
			if (m_state == State::Growing)
			{
				m_bSmall = false;
			}
			//��������
			else if (m_state == State::ProducingSun)
			{
				this->productSun();
			}
			//�л�״̬
			this->changeState(State::Normal);
		}
	}
}

void SunShroom::onSleepingEnter()
{
	this->changeState(State::Sleeping);
}

void SunShroom::onSleepingExit()
{
	this->changeState(State::Normal);
}

void SunShroom::growUpdate(float dt)
{
	//��ǰ�ɳ�ʱ��ʣ��
	if (m_growUpTimeLeft > 0.f)
	{
		m_growUpTimeLeft -= dt;
		//����ɳ�ʱ�䣬�ɳ�
		if (m_growUpTimeLeft <= 0.f)
		{
			this->changeState(State::Growing);
		}
	}
}

void SunShroom::productSun()
{
	//����һ������
	Size size = this->getContentSize(); 
	auto x = RANDOM(0.f,size.width);
	auto y = 0.f;
	
	JumpBy*jump = JumpBy::create(0.8f,Point(x,y),-size.height,1);
	auto pos = this->getPosition();
	auto realPos = this->getParent()->convertToWorldSpace(pos);
	//ȷ����Ҫ�������������
	int number = m_bSmall ? 15 : 25;

	m_pDelegate->makeSun(number,jump,realPos);
}

void SunShroom::changeState(State state)
{
	if (m_state == state)
		return ;

	m_state = state;

	string animationName;
	auto plantName = this->getPlantName();
	Animation*animation = nullptr;

	if (state == State::Normal)
	{
		if (m_bSmall)
		{
			animationName = StringUtils::format("%s2",plantName.c_str());
		}
		else
			animationName = plantName;
		//ֹͣԭ�ȵĶ���
		this->getSprite()->stopActionByTag(ANIMATION_TAG);

		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::Sleeping)
	{
		animationName = StringUtils::format("%sSleep",plantName.c_str());
		//ֹͣԭ�ȵĶ���
		this->getSprite()->stopActionByTag(ANIMATION_TAG);
	
		animation = AnimationCache::getInstance()->getAnimation(animationName);
		m_duration = animation->getDuration();
	}
	else if (state == State::Growing)
	{
		animationName = StringUtils::format("%sGrowing",plantName.c_str());
		//ֹͣԭ�ȵĶ���
		this->getSprite()->stopActionByTag(ANIMATION_TAG);
	
		animation = AnimationCache::getInstance()->getAnimation(animationName);
		m_duration = animation->getDuration();
	}
	else if (state == State::ProducingSun)
	{
		//�������� ʱ��
		m_duration = 2.f;
		//�ı�color mod
		this->getSprite()->setColorMod(Color3B(0xee,0xc9,0x00));
	}
	if (animation != nullptr)
	{
		auto animate = Animate::create(animation);
		animate->setTag(ANIMATION_TAG);

		this->getSprite()->runAction(animate);
		//�ָ�ԭ������ɫ
		this->getSprite()->setColorMod(Color3B(0xff,0xff,0xff));
	}
}